#include "Player.hpp"

Player::Player(int x, int y, std::string filename)
{
	// player starts facing right b/c images have him facing right
	facingRight = true;
	dead = false;

	// player starts standing
	currentAnimation = STANDING;
	teleporting = false;
	isDying = false;
	dyingAnimationStarted = false;

	numHealthPotions = 0;
	numInvincibilityPotions = 0;
	invAccumulator = 5000;
	invTime = 3000;
	invPrevTime = c->getElapsedTime().asMilliseconds();

	delay = 250;

	height = 100;
	width = 60;

	this->x = x;
	this->y = y;

	dx = 0;
	dy = 0;

	if (!texture->loadFromFile(filename))
	{
		std::cout << "Failed to load player image." << std::endl;
	}
	sprite->setTexture(*texture);

	standing = new Frame;
	walking = new Frame;
	dying = new Frame;
	teleportStart = new Frame;
	teleportEnd = new Frame;

	// player frames are 60x100
	standing->addFrame(sf::IntRect(0, 0, 60, 100));

	// to find a subimage, you have to give the starting x and y coordinate
	// and how far you want it to keep going
	for (int k = 0; k < 4; ++k)
	{
		walking->addFrame(sf::IntRect(k * 60, 100, 60, 100));
	}

	// dying animation contains 2 rows of 7 in the spritesheet
	for (int i = 0; i < 7; ++i)
	{
		dying->addFrame(sf::IntRect(i * 60, 200, 60, 100));
	}
	for (int j = 0; j < 7; ++j)
	{
		dying->addFrame(sf::IntRect(j * 60, 300, 60, 100));
	}

	// teleport contains 2 rows of 7 seven plus 2 frames
	for (int i = 0; i < 7; ++i)
	{
		teleportStart->addFrame(sf::IntRect(i * 60, 400, 60, 100));
	}

	for (int i = 0; i < 7; ++i)
	{
		teleportStart->addFrame(sf::IntRect(i * 60, 500, 60, 100));
	}

	for (int i = 0; i < 2; ++i)
	{
		teleportStart->addFrame(sf::IntRect(i * 60, 600, 60, 100));
	}

	// teleport end uses teleport start images backwards
	for (int i = 1; i >= 0; --i)
	{
		teleportEnd->addFrame(sf::IntRect(i * 60, 600, 60, 100));
	}

	for (int i = 6; i >= 0; --i)
	{
		teleportEnd->addFrame(sf::IntRect(i * 60, 500, 60, 100));
	}

	for (int i = 6; i >= 0; --i)
	{
		teleportEnd->addFrame(sf::IntRect(i * 60, 400, 60, 100));
	}

	// standing is one frame so it uses -1 for delay (which is default)
	// 2 steps/sec. 2 steps * 4 frames = 8 frames per second for running
	walking->setDelay(1000 / 8);
	// 14 frames over 100 milliseconds
	dying->setDelay(100 / 14);

	teleportStart->setDelay(100 / 16);
	teleportEnd->setDelay(100 / 16);

	sprite->setFrames(*standing);
	sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
	sprite->setPosition(sf::Vector2f(x, y));

	healthBar = new HealthBar(x - sprite->getGlobalBounds().width / 2, y - sprite->getGlobalBounds().height / 2 - 10);
	health = maxHealth;
	damage = 5;

}

void Player::update(const BoundingBox &box)
{
	move(box);
	checkBounds();
	if (!dead)
		sprite->update();
	setPosition(x, y);
	healthBar->setHealth(health);
	invincibleTimer();
	healthBar->update(x - sprite->getGlobalBounds().width / 2, y - sprite->getGlobalBounds().height / 2 - 10);
}

void Player::draw(sf::RenderWindow *window)
{
	window->draw(*sprite);
	healthBar->draw(window);
}

void Player::hit(int damage)
{
	if (!isInvincible())
	{
		health -= damage;
		if (health <= 0)
		{
			health = 0;
			isDying = true;
		}
	}
}

void Player::move(const BoundingBox &box)
{
	// slow down the player. if no input is received, then the player eventually stops
	dx = dx * friction;
	dy = dy * friction;

	// get box position, width etc for collision detection
	int bx = box.getX();
	int by = box.getY();
	int brickHeight = box.getHeight();
	int brickWidth = box.getWidth();

	if (dead)
		return;

	// player is dying
	if (isDying)
	{
		// if the animation isn't dying, set it to dying
		if (currentAnimation != DYING)
		{
			currentAnimation = DYING;
			sprite->setFrames(*dying);
			// don't let player move
			dx = 0;
			dy = 0;
			dyingAnimationStarted = true;
		}
		// if death animation has played, signal that player is dead
		if (sprite->hasPlayedOnce() && currentAnimation == DYING)
		{
			dead = true;
		}
		// don't let other animations play
		return;
	}

	if (teleporting)
	{
		// teleport has two parts; check whether teleport has not started or ended
		if (currentAnimation != TELEPORT_START && currentAnimation != TELEPORT_END)
		{
			sprite->setFrames(*teleportStart);
			currentAnimation = TELEPORT_START;
		}
		// first part of teleport has been played, so play second part.
		// However, it can't be equal to TELEPORT_START, or it'll get messed up
		if (sprite->hasPlayedOnce() && currentAnimation == TELEPORT_START)
		{
			sprite->setFrames(*teleportEnd);
			currentAnimation = TELEPORT_END;
			x = teleportX;
			y = teleportY;

			// check whether player is inside bricks
			// if he is, then move him out of there
			// collision with top side of brick
			if (y + height / 2 > (by - brickHeight / 2) && y < (by) && x + width / 2 >(bx - brickWidth / 2) && x - width / 2 < (bx + brickWidth / 2))
			{
				dy = 0;
				y = by - brickHeight / 2 - height / 2;
			}

			// collision with left side of brick
			else if (x + width / 2 > (bx - brickWidth / 2) && x < (bx) && y + height / 2 >(by - brickHeight / 2) && y - height / 2 < (by + brickHeight / 2))
			{
				dx = 0;
				x = bx - brickWidth / 2 - width / 2;
			}

			// collision with right side of brick
			if (x - width / 2 < (bx + brickWidth / 2) && x > (bx) && y + height / 2 > (by - brickHeight / 2) && y - height / 2 < (by + brickHeight / 2))
			{
				dx = 0;
				x = bx + brickWidth / 2 + width / 2;
			}

			// collision with bottom side of brick
			else if (y - height / 2 < (by + brickHeight / 2) && y > (by) && x + width / 2 > (bx - brickWidth / 2) && x - width / 2 < (bx + brickWidth / 2))
			{
				dy = 0;
				y = by + brickHeight / 2 + height / 2;
			}

			dx = dy = 0;
			return;
		}
		// check whether second half of teleport has ended
		if (sprite->hasPlayedOnce() && currentAnimation == TELEPORT_END)
		{
			teleporting = false;
			currentAnimation = WALKING;
			sprite->setFrames(*standing);
		}

		return;
	}

	if (movedRight)
	{
		dx += acceleration;
		if (dx > maxSpeed)
			dx = maxSpeed;
		if (currentAnimation != WALKING)
		{
			sprite->setFrames(*walking);
			currentAnimation = WALKING;
		}
		// if player is facing left when moving right, make him face left
		if (!facingRight)
		{
			facingRight = true;
			sprite->setScale(1, 1);
		}
	}
	if (movedLeft)
	{
		dx -= acceleration;
		if (dx < -maxSpeed)
			dx = -maxSpeed;
		if (currentAnimation != WALKING)
		{
			sprite->setFrames(*walking);
			currentAnimation = WALKING;
		}
		// if player is facing right when moving left, make him face left
		if (facingRight)
		{
			facingRight = false;
			sprite->setScale(-1, 1);
		}
	}
	if (movedUp)
	{
		if (currentAnimation != WALKING)
		{
			sprite->setFrames(*walking);
			currentAnimation = WALKING;
		}
		dy -= acceleration;
		if (dy < -maxSpeed)
			dy = -maxSpeed;
	}
	if (movedDown)
	{
		if (currentAnimation != WALKING)
		{
			sprite->setFrames(*walking);
			currentAnimation = WALKING;
		}
		dy += acceleration;
		if (dy > maxSpeed)
			dy = maxSpeed;
	}
	if (!(movedDown || movedLeft || movedUp || movedRight))
	{
		// if player's velocity is between 1 and 0 or -1 and 0 stop him
		if (dx > 0 && dx < 1)
			dx = 0;
		else if (dx < 0 && dx > -1)
			dx = 0;
		if (dy > 0 && dx < 1)
			dy = 0;
		if (dy < 0 && dx > -1)
			dy = 0;

		if (currentAnimation != STANDING)
		{
			sprite->setFrames(*standing);
			currentAnimation = STANDING;
		}
	}

	checkBrickCollision(box);

	x = tempx + dx;
	y = tempy + dy;
}

void Player::teleport(int x, int y)
{
	// teleport to target (x and y)
	teleportX = x;
	teleportY = y;
	teleporting = true;
}

void Player::addInvincibilityPotion()
{
	numInvincibilityPotions += 1;
}

int Player::getNumInvincibilityPotions()
{
	return numInvincibilityPotions;
}

void Player::setInvincible()
{
	if (numInvincibilityPotions > 0)
	{
		invAccumulator = 0;
		numInvincibilityPotions--;
	}
}

bool Player::isInvincible()
{
	return invincibleTimer();
}

bool Player::invincibleTimer()
{
	invCurrentTime = c->getElapsedTime().asMilliseconds();
	invAccumulator += invCurrentTime - invPrevTime;
	invPrevTime = invCurrentTime;
	if (invAccumulator > invTime)
	{
		return false;
	}
	return true;
}

void Player::addHealthPotion()
{
	numHealthPotions += 1;
}

int Player::getNumHealthPotions()
{
	return numHealthPotions;
}

void Player::heal()
{
	if (numHealthPotions > 0)
	{
		health += HEAL_AMOUNT;
		numHealthPotions--;
		if (health > maxHealth)
			health = maxHealth;
	}
}

int Player::getDamage()
{
	return damage;
}

void Player::setTeleporting(bool b)
{
	teleporting = b;
}

bool Player::getTeleporting() const
{
	return teleporting;
}

bool Player::getTeleporting()
{
	return teleporting;
}

bool Player::isDead()
{
	return dead;
}

bool Player::hasDyingAnimationStarted()
{
	if (dyingAnimationStarted)
		return true;
	return false;

}

int Player::getStaffX()
{
	// staff is at x = 55
	// if player is facing right, staff is on right side, so x has to be added
	// if player is facing left, staff is on left side, so x has to be subtracted
	if (facingRight)
		return x - width / 2 + 55;
	return x + width / 2 - 55;
}

int Player::getStaffY()
{
	// staff is at y = 56
	return y - height / 2 + 56;
}

void Player::setMovedDown(bool b)
{
	movedDown = b;
}

void Player::setMovedUp(bool b)
{
	movedUp = b;
}

void Player::setMovedRight(bool b)
{
	movedRight = b;
}

void Player::setMovedLeft(bool b)
{
	movedLeft = b;
}

bool Player::getMovedDown()
{
	return movedDown;
}

bool Player::getMovedUp()
{
	return movedUp;
}

bool Player::getMovedRight()
{
	return movedRight;
}

bool Player::getMovedLeft()
{
	return movedLeft;
}

Player::~Player()
{
	delete standing;
	delete walking;
	delete dying;
	delete teleportStart;
	delete teleportEnd;
}
