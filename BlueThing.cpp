#include "BlueThing.hpp"

BlueThing::BlueThing(int x, int y)
{
	this->x = x;
	this->y = y;

	dx = 0;
	dy = 0;

	speed = 3;

	height = 52;
	width = 52;

	currentAnimation = STANDING;

	health = maxHealth;
	damage = 5;

	delay = 400;
	reloading = false;
	startReload = false;
	reloadAccumulator = 1000;

	if (!texture->loadFromFile(filename))
	{
		std::cout << "not able to load BlueThing texture" << std::endl;
	}
	sprite->setTexture(*texture);

	for (int i = 0; i < 10; ++i)
	{
		dying->addFrame(sf::IntRect(i * 52, 52, 52, 52));
	}
	dying->setDelay(10 / 100);
	standing->addFrame(sf::IntRect(0, 0, 52, 52));
	sprite->setFrames(*standing);
	sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);

	healthBar->update(x - sprite->getGlobalBounds().width / 2, y - sprite->getGlobalBounds().height);
}

void BlueThing::update(const Entity &e, const BoundingBox &box)
{
	if (dead)
		return;

	sprite->update();
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
		}
		// if death animation has played, signal that player is dead
		if (sprite->hasPlayedOnce() && currentAnimation == DYING && health == 0)
		{
			dead = true;
		}
		// don't let other animations play
		return;
	}

	if (numTimesFired > 5)
	{
		reloading = true;
		startReload = true;
		numTimesFired = 0;
	}
	moveTowardsPlayer(e);
	checkBrickCollision(box);
	checkBounds();

	// set x and y equal to the new values
	x = tempx + dx;
	y = tempy + dy;
	setPosition(x, y);
	healthBar->update(x - sprite->getGlobalBounds().width / 2, y - sprite->getGlobalBounds().height / 2);
}

void BlueThing::draw(sf::RenderWindow *window)
{
	window->draw(*sprite);
	healthBar->draw(window);
}

bool BlueThing::isReloading()
{
	static int reloadTime = 600;
	static int reloadCurrentTime;
	static int reloadPrevTime = c->getElapsedTime().asMilliseconds();
	if (startReload)
	{
		reloadAccumulator = 0;
		startReload = false;
	}
	reloadCurrentTime = c->getElapsedTime().asMicroseconds() / 1000;
	reloadAccumulator += reloadCurrentTime - reloadPrevTime;
	reloadPrevTime = reloadCurrentTime;
	if (reloadAccumulator < reloadTime)
	{
		if (reloading)
		{
			reloading = false;
			return true;
		}

	}
	return false;
}

std::unique_ptr<BlueThing> BlueThing::create(int x, int y)
{
	std::unique_ptr<BlueThing> b(new BlueThing(x, y));

	return b;
}

BlueThing::~BlueThing()
{
	
}
