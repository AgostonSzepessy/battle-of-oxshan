#include "PlayState.hpp"

PlayState::PlayState(sf::RenderWindow *window, GameStateManager *gsm) : GameState(window, gsm)
{
	create();
	makeBricks();
	createWave();
}

std::unique_ptr<PlayState> PlayState::build(sf::RenderWindow *window, GameStateManager *gsm)
{
	std::unique_ptr<PlayState> playState(new PlayState(window, gsm));

	return playState;
}

void PlayState::update()
{
	srand(time(NULL));
	handleInput();

	player->update(*boundingBox);

	// if the player's dying animation has started,
	// then play the dying sound
	if (player->hasDyingAnimationStarted())
		sounds[PLAYER_DYING]->play();

	// if the player dies, switch to GameOverState
	if (player->isDead())
	{
		gsm->pushState(GameOverState::build(window, gsm, waveNumber));
	}
	// update enemies
	if (!enemies.empty())
	{
		for (unsigned j = 0; j < enemies.size(); ++j)
		{
			// keeps track of whether the current enemy is dead
			// because if it's not, then there's a segfault
			bool enemyDead = false;
			if (enemies[j]->isDead())
			{
				// before dying, create a powerup
				int potionType = rand() % 6;
				if (potionType == 0)
					powerups.push_back(std::move(HealthUp::create(enemies[j]->getX(), enemies[j]->getY())));
				else if (potionType == 1)
					powerups.push_back(std::move(InvincibilityUp::create(enemies[j]->getX(), enemies[j]->getY())));
				// set to true so the enemy is not updated further (if it was, then there would be a segfault)
				enemyDead = true;
				// different enemies have different dying sounds
				if (typeid(*enemies[j]).name() == typeid(BlueThing).name())
					sounds[BLUETHING_DYING]->play();
				else
					sounds[SORCERER_DYING]->play();
				// erase enemy from vector
				enemies.erase(enemies.begin() + j);
			}
			// move enemies towards player, if the enemy isn't dead
			if (!enemyDead)
			{
				// move enemy towards player
				enemies[j]->update(*player, *boundingBox);

				if (enemies[j]->canFire())
				{
					if (typeid(*enemies[j]).name() == typeid(BlueThing).name())
					{
						// only bluething has to reload
						if (enemies[j]->isReloading())
							sounds[BLUETHING_RELOAD]->play();
						else
						{
							// add bullets around the BlueThing in a circle
							addBullet(EnemyBullet::create(enemies[j]->getX(), enemies[j]->getY(), enemies[j]->getX() - 10, enemies[j]->getY() + 20, enemies[j]->getDamage(), BULLET));
							sounds[BLUETHING_FIRING]->play();
							addBullet(EnemyBullet::create(enemies[j]->getX(), enemies[j]->getY(), enemies[j]->getX() - 10, enemies[j]->getY() - 20, enemies[j]->getDamage(), BULLET));
							sounds[BLUETHING_FIRING]->play();
							addBullet(EnemyBullet::create(enemies[j]->getX(), enemies[j]->getY(), enemies[j]->getX() - 10, enemies[j]->getY(), enemies[j]->getDamage(), BULLET));
							sounds[BLUETHING_FIRING]->play();
							addBullet(EnemyBullet::create(enemies[j]->getX(), enemies[j]->getY(), enemies[j]->getX() + 10, enemies[j]->getY() + 20, enemies[j]->getDamage(), BULLET));
							sounds[BLUETHING_FIRING]->play();
							addBullet(EnemyBullet::create(enemies[j]->getX(), enemies[j]->getY(), enemies[j]->getX() + 10, enemies[j]->getY() - 20, enemies[j]->getDamage(), BULLET));
							sounds[BLUETHING_FIRING]->play();
							addBullet(EnemyBullet::create(enemies[j]->getX(), enemies[j]->getY(), enemies[j]->getX() + 10, enemies[j]->getY(), enemies[j]->getDamage(), BULLET));
							sounds[BLUETHING_FIRING]->play();
							enemies[j]->addToNumTimesFired();
						}
					}
					if (typeid(*enemies[j]).name() == typeid(Sorcerer).name())
					{
						// make the Sorcerer shoot towards the player
						addBullet(EnemyBullet::create(enemies[j]->getX(), enemies[j]->getY(), player->getX(), player->getY(), enemies[j]->getDamage(), LIGHTNING_BOLT));
						sounds[SORCERER_FIRING]->play();
					}
				}
			}
		}
	}
	// if the enemies have been killed, and the
	// waveText has not been set to 'Continue...',
	// then set it
	else if (enemies.empty() && !hasSetText)
	{
		setContinueText();
	}

	// update bullets
	if (!bullets.empty())
	{
	startloop:
		for (unsigned i = 0; i < bullets.size(); ++i)
		{
			// check whether pointer is null to prevent segfault
			if (bullets[i])
			{
				// check whether the bullet is out of bounds, because if it is it's wasting memory
				if (bullets[i]->outOfBounds())
				{
					bullets.erase(bullets.begin() + i);
					i--;
				}
				else
				{
					bullets[i]->update();

					if (bullets[i]->checkCollision(*boundingBox))
					{
						if (typeid(*bullets[i]).name() == typeid(PlayerBullet).name())
							sounds[FIREBALL_EXPLOSION]->play();
						bullets.erase(bullets.begin() + i);

						// bullet hit, no need to check any other bricks
						goto startloop;
					}

					for (unsigned j = 0; j < enemies.size(); ++j)
					{
						// check whether the bullet is a player bullet so it can kill the enemy
						if (typeid(*bullets[i]).name() == typeid(PlayerBullet).name())
						{
							if (bullets[i]->checkCollision(*enemies[j]))
							{
								enemies[j]->hit(bullets[i]->getDamage());
								bullets.erase(bullets.begin() + i);
								sounds[FIREBALL_EXPLOSION]->play();
								sounds[ENEMY_HIT]->play();
								// bullet hit enemy, no need to check anymore of them so restart
								goto startloop;
							}
						}
					}
					// no need to check if it's an enemy bullet if there aren't any enemies
					if (enemies.size() != 0)
					{
						if (typeid(*bullets[i]).name() == typeid(EnemyBullet).name())
						{
							if (bullets[i]->checkCollision(*player))
							{
								player->hit(bullets[i]->getDamage());
								bullets.erase(bullets.begin() + i);
								sounds[PLAYER_HIT]->play();
							}
						}
					}
				}
			}
		}
	}

	// loop through all the power ups and check if the player
	// collides with them.
	for (unsigned i = 0; i < powerups.size(); ++i)
	{
		// this is used to prevent segfaults
		bool collided = false;
		// check collision with power ups
		if (powerups[i]->checkCollision(*player))
		{
			sounds[POWERUP]->play();
			// if it's a health potion, add a health potion to player
			if (typeid(*powerups[i]).name() == typeid(HealthUp).name())
			{
				powerups[i]->effect(*player);
				powerups.erase(powerups.begin() + i);
				collided = true;
			}
			// use collided whether the potion needs to be checked
			// to see if it is an invincibility potion
			if (!collided)
			{
				if (typeid(*powerups[i]).name() == typeid(InvincibilityUp).name())
				{
					powerups[i]->effect(*player);
					powerups.erase(powerups.begin() + i);
				}
			}
		}
	}

	// set the number of potions collected
	healthPotionsCollected->setString("Health Potions:" + std::to_string(player->getNumHealthPotions()));
	if (player->isInvincible())
		invincibilityPotionsCollected->setString("Invincibility Potions (On): " + std::to_string(player->getNumInvincibilityPotions()));
	else if (!player->isInvincible())
		invincibilityPotionsCollected->setString("Invincibility Potions (Off): " + std::to_string(player->getNumInvincibilityPotions()));

	// if the "continue to next wave" text has been set,
	// and the player pressed tab, then continue to next wave
	if (hasSetText && continueToNextWave)
	{
		createWave();
	}
}

void PlayState::draw()
{
	window->clear(sf::Color::Green);

	background->draw(window);

	for (unsigned i = 0; i < bricks.size(); ++i)
	{
		bricks[i]->draw(window);
	}

	player->draw(window);

	for (unsigned i = 0; i < bullets.size(); ++i)
	{
		bullets[i]->draw(window);
	}

	for (unsigned i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->draw(window);
	}

	for (unsigned i = 0; i < powerups.size(); ++i)
	{
		powerups[i]->draw(window);
	}

	if (!deleteText() || hasSetText)
		window->draw(*waveText);

	window->draw(*healthPotionsCollected);
	window->draw(*invincibilityPotionsCollected);

	window->display();
}

void PlayState::handleInput()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
		{
			gsm->quit();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			// if player presses escape, pause game
			if (event.key.code == sf::Keyboard::Escape)
			{
				gsm->pushState(PauseState::build(window, gsm));
			}
			if (event.key.code == sf::Keyboard::R)
			{
				player->heal();
				// 			waveText->setString("Health Potions:" + std::to_string(player->getNumHealthPotions()));
			}
			if (event.key.code == sf::Keyboard::Q)
			{
				player->setInvincible();
				invincibilityPotionsCollected->setString("Invincibility Potions (On): " + std::to_string(player->getNumInvincibilityPotions()));
			}
		}
	}

	// moving right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player->setMovedRight(true);
	else
		player->setMovedRight(false);

	// moving left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		player->setMovedLeft(true);
	else
		player->setMovedLeft(false);

	// moving down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		player->setMovedDown(true);
	else
		player->setMovedDown(false);

	// moving up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		player->setMovedUp(true);
	else
		player->setMovedUp(false);

	// teleports player to mouse position
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		player->teleport(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
	}

	// fire bullet
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (player->canFire())
		{
			addBullet(PlayerBullet::create(player->getStaffX(), player->getStaffY(), sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y, player->getDamage()));
			sounds[PLAYER_FIRING]->play();
		}
	}
	// if the current wave is still going, block the tab input, so the
	// next wave doesn't start right after the current one is done
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && !isWaveActive)
	{
		continueToNextWave = true;
	}
}

void PlayState::create()
{
	// initialize variables

	player = new Player(100, 100, "res/sprites/player/player-spritesheet.png");

	waveText = new sf::Text;
	font = new sf::Font;

	healthPotionsCollected = new sf::Text;
	invincibilityPotionsCollected = new sf::Text;

	font = new sf::Font;
	if (!font->loadFromFile("res/fonts/arial.ttf"))
	{
		std::cout << "not able to load arial font" << std::endl;
	}

	healthPotionsCollected->setFont(*font);
	healthPotionsCollected->setCharacterSize(16);
	healthPotionsCollected->setColor(sf::Color::Black);
	healthPotionsCollected->setString("Health Potions:");
	healthPotionsCollected->setOrigin(healthPotionsCollected->getGlobalBounds().width / 2, healthPotionsCollected->getGlobalBounds().height / 2);
	healthPotionsCollected->setPosition(WIDTH - healthPotionsCollected->getGlobalBounds().width + 20, HEIGHT - healthPotionsCollected->getGlobalBounds().height - 10);

	invincibilityPotionsCollected->setFont(*font);
	invincibilityPotionsCollected->setCharacterSize(16);
	invincibilityPotionsCollected->setColor(sf::Color::Black);
	invincibilityPotionsCollected->setString("Invincibility Potions (Off):");
	invincibilityPotionsCollected->setOrigin(invincibilityPotionsCollected->getGlobalBounds().width / 2, invincibilityPotionsCollected->getGlobalBounds().height / 2);
	invincibilityPotionsCollected->setPosition(WIDTH - invincibilityPotionsCollected->getGlobalBounds().width + 53, HEIGHT - healthPotionsCollected->getGlobalBounds().height - 25);

	waveText->setFont(*font);
	waveText->setCharacterSize(textSize);
	waveText->setColor(textColor);

	c = new sf::Clock;

	background = std::move(Background::create("res/backgrounds/grass.png"));

	waveNumber = 0;

	delay = 1000;
	currentTime = 0;
	accumulator = 0;
	prevTime = c->getElapsedTime().asMilliseconds();
	continueToNextWave = false;
	isWaveActive = false;
	setTimer = false;

	for (int i = 0; i < ENEMY_HIT + 1; ++i)
	{
		soundBuffers.push_back(std::move(createSoundBuffer()));
	}

	if (!soundBuffers[PLAYER_FIRING]->loadFromFile("res/sfx/player-shoot.ogg"))
		std::cout << "unable to load player-shoot.ogg" << std::endl;
	if (!soundBuffers[PLAYER_HIT]->loadFromFile("res/sfx/hit.ogg"))
		std::cout << "unable to load hit.ogg" << std::endl;
	if (!soundBuffers[PLAYER_DYING]->loadFromFile("res/sfx/player-dying.ogg"))
		std::cout << "unable to load player-dying.ogg" << std::endl;
	if (!soundBuffers[FIREBALL_EXPLOSION]->loadFromFile("res/sfx/fireball-explosion.ogg"))
		std::cout << "unable to load fireball-explosion.ogg" << std::endl;
	if (!soundBuffers[POWERUP]->loadFromFile("res/sfx/powerup.ogg"))
		std::cout << "unable to load powerup.ogg" << std::endl;
	if (!soundBuffers[BLUETHING_FIRING]->loadFromFile("res/sfx/gunshot-bluething.ogg"))
		std::cout << "unable to load gunshot-bluething.ogg" << std::endl;
	if (!soundBuffers[BLUETHING_RELOAD]->loadFromFile("res/sfx/bluething-reload.ogg"))
		std::cout << "unable to load bluething-reload.ogg" << std::endl;
	if (!soundBuffers[BLUETHING_DYING]->loadFromFile("res/sfx/bluething-dying.ogg"))
		std::cout << "unable to load bluething-dying.ogg" << std::endl;
	if (!soundBuffers[SORCERER_FIRING]->loadFromFile("res/sfx/sorcerer-fire.ogg"))
		std::cout << "unable to load sorcerer-fire.ogg" << std::endl;
	if (!soundBuffers[SORCERER_DYING]->loadFromFile("res/sfx/sorcerer-dying.ogg"))
		std::cout << "unable to load sorcerer-dying.ogg" << std::endl;
	if (!soundBuffers[ENEMY_HIT]->loadFromFile("res/sfx/enemy-hit.ogg"))
		std::cout << "unable to load enemy-hit.ogg" << std::endl;

	for (int i = 0; i < ENEMY_HIT + 1; ++i)
	{
		sounds.push_back(std::move(createSound()));
		sounds[i]->setBuffer(*soundBuffers[i]);
	}

}

void PlayState::addBullet(std::unique_ptr<Bullet> b)
{
	bullets.push_back(std::move(b));
}

void PlayState::makeBricks()
{
	/*
	* This figures out where the bricks can be drawn. It creates
	* a rectangular region, and then picks a direction of the bricks
	* in the x or y direction. Then it makes the area smaller, so it
	* starts drawing there, because it draws from left to right. Then
	* an offset is added and a the xsize is multiplied by a random
	* percentage, and the bricks are drawn.
	*/

	srand(time(NULL));

	// calculating the bounds that the brick is allowed to exist in; leaving a margin
	int xsize = WIDTH - 2 * player->getWidth();
	int ysize = HEIGHT - 2 * player->getHeight();

	// number of bricks to make and their direction
	int bricksToMake = (rand() % 2) + 2;
	int direction = rand() % 2;

	// horizontal
	if (direction == 0)
	{
		// the brick isn't 0 size, it's going to take up one brick size
		// vertically, but bricksToMake * BRICK_SIZE horizontally
		xsize -= bricksToMake * BRICK_SIZE;
		ysize -= BRICK_SIZE;
	}
	else
	{
		xsize -= BRICK_SIZE;
		ysize -= bricksToMake * BRICK_SIZE;
	}

	// add offset to put it in right position
	int x = player->getWidth() + xsize * ((float)rand() / RAND_MAX);
	int y = player->getHeight() + ysize * ((float)rand() / RAND_MAX);

	// sets the position of the brics by either adding to the x position,
	// or the y position
	for (int i = 1; i <= bricksToMake; ++i)
	{
		bricks.push_back(std::move(Brick::create(x + BRICK_SIZE / 2, y + BRICK_SIZE / 2)));
		if (direction == 0) {
			x += BRICK_SIZE;
		}
		else {
			y += BRICK_SIZE;
		}
	}

	boundingBox = new BoundingBox(bricks);

	powerups.push_back(std::move(HealthUp::create(500, 300)));
	powerups.push_back(std::move(InvincibilityUp::create(400, 500)));
}

void PlayState::setContinueText()
{
	// set text
	waveText->setString("Press Tab to contine to the Next Wave");
	waveText->setOrigin(waveText->getGlobalBounds().width / 2, waveText->getGlobalBounds().height / 2);
	waveText->setPosition(WIDTH / 2, HEIGHT / 2);
	// this makes sure this function isn't called again before next wave is done
	hasSetText = true;
	// this allows the player to start the next wave when he presses tab
	isWaveActive = false;
	// display this message until player presses Tab
	setTimer = false;
}

void PlayState::createWave()
{
	// by setting these to false, setContinueText(), can't be called
	hasSetText = continueToNextWave = false;
	// block input when player presses tab, so the next wave doesn't start right after
	// the current one is done
	isWaveActive = true;
	// use timer to display waveText
	setTimer = true;
	// increase wave number by one
	waveNumber++;

	// generate random enemy positions
	srand(time(NULL));

	switch (waveNumber)
	{
	case 1:
		enemies.push_back(std::move(Sorcerer::create(rand() % WIDTH, rand() % HEIGHT)));
		break;
	case 2:
		for (int i = 0; i < 2; ++i)
		{
			enemies.push_back(std::move(Sorcerer::create(rand() % WIDTH, rand() % HEIGHT)));
		}
		break;
	default:
		// generate 5 enemies max
		int numEnemies = rand() % 4 + 1;

		if (numEnemies < 2)
			numEnemies = 3;

		// two different types of enemies can be created
		// based on how many were generated
		//int enemyType[numEnemies];
		int *enemyType = new int[numEnemies];

		// loop through enemies and assign them random enemy types: BlueThing or Sorcerer
		for (int i = 0; i < numEnemies; ++i)
		{
			// assign random type
			enemyType[i] = rand() % 4;
			// if number is 0 or 2, it's a BlueThing, also generate random positions
			if (enemyType[i] == 0 || enemyType[i] == 2)
			{
				int x = rand() % WIDTH;
				int y = rand() % HEIGHT;
				enemies.push_back(std::move(BlueThing::create(x, y)));
			}
			// if number is 1 or 3, it's a Sorcerer, also generate random positions
			else if (enemyType[i] == 1 || enemyType[i] == 3)
			{
				int x = rand() % WIDTH;
				int y = rand() % HEIGHT;
				enemies.push_back(std::move(Sorcerer::create(x, y)));
			}
			delete[] enemyType;
		}
	}

	// set waveText text to wave number, and set its position to the middle of the screen
	waveText->setString("Wave " + std::to_string(waveNumber));
	waveText->setOrigin(waveText->getGlobalBounds().width / 2, waveText->getGlobalBounds().height / 2);
	waveText->setPosition(WIDTH / 2, HEIGHT / 2);
}

bool PlayState::deleteText()
{
	// if the timer needs to be started,
	// then set accumulator to 0, and that'll
	// count to 1 second
	if (setTimer)
	{
		accumulator = 0;
		setTimer = false;
	}
	currentTime = c->getElapsedTime().asMilliseconds();
	accumulator += currentTime - prevTime;
	prevTime = currentTime;
	if (accumulator > delay)
	{
		// if accumulator is greater than delay, hide text
		return true;
	}
	// if accumulator isn't greater than one second (delay), then display text (don't hide it)
	return false;
}

std::unique_ptr<sf::SoundBuffer> PlayState::createSoundBuffer()
{
	std::unique_ptr<sf::SoundBuffer> sb(new sf::SoundBuffer);
	return sb;
}

std::unique_ptr<sf::Sound> PlayState::createSound()
{
	std::unique_ptr<sf::Sound> s(new sf::Sound);
	return s;
}

PlayState::~PlayState()
{
	delete player;
	delete boundingBox;
	delete font;
	delete waveText;
	delete c;
	delete healthPotionsCollected;
	delete invincibilityPotionsCollected;

	enemies.clear();
	bullets.clear();
	bricks.clear();
	powerups.clear();
	sounds.clear();
	soundBuffers.clear();

}
