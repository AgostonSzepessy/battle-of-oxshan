#include "Sorcerer.hpp"

Sorcerer::Sorcerer(int x, int y) : Enemy()
{
	this->x = x;
	this->y = y;
	dx = dy = 0;

	currentSide = TOP_SIDE;

	health = maxHealth;
	damage = 7;

	speed = 4;

	width = height = 50;
	teleporting = false;

	walking = new Frame();
	teleportStart = new Frame();
	teleportEnd = new Frame();

	currentAnimation = STANDING;

	standing->addFrame(sf::IntRect(0, 0, 50, 50));

	// set walking frames
	for (int i = 0; i < 8; ++i)
	{
		walking->addFrame(sf::IntRect(i * 50, 50, 50, 50));
	}

	// set first half of teleport frames
	for (int i = 0; i < 8; ++i)
	{
		teleportStart->addFrame(sf::IntRect(i * 50, 100, 50, 50));
	}

	for (int i = 0; i < 8; ++i)
	{
		teleportStart->addFrame(sf::IntRect(i * 50, 150, 50, 50));
	}
	// last frame is one line by itself
	teleportStart->addFrame(sf::IntRect(0, 200, 50, 50));

	// teleport end frames; they are the same as teleport start, except backwards
	teleportEnd->addFrame(sf::IntRect(0, 200, 50, 50));
	for (int i = 7; i >= 0; --i)
	{
		teleportEnd->addFrame(sf::IntRect(i * 50, 150, 50, 50));
	}

	for (int i = 7; i >= 0; --i)
	{
		teleportEnd->addFrame(sf::IntRect(i * 50, 100, 50, 50));
	}

	// the dying frames are 50x55, so they are taller
	for (int i = 0; i < 8; ++i)
	{
		dying->addFrame(sf::IntRect(i * 50, 250, 50, 55));
	}

	for (int i = 0; i < 2; ++i)
	{
		dying->addFrame(sf::IntRect(i * 50, 305, 50, 55));
	}

	// standing has default of -1, because it doesn't need to update; it's just standing there

	// walking has 8 frames. There are 4 steps in one second, so 8 * 2 = 16
	walking->setDelay(1000 / 16);

	// 10 frames over 100 milliseconds for dying
	dying->setDelay(150 / 10);

	// 17 frames over 100 milliseconds
	teleportStart->setDelay(100 / 17);
	teleportEnd->setDelay(100 / 17);

	if (!texture->loadFromFile(filename))
	{
		std::cout << "not able to load BlueThing texture" << std::endl;
	}
	sprite->setTexture(*texture);

	// set sprite to standing and set its origin in the center, then set its position
	sprite->setFrames(*standing);
	sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
	sprite->setPosition(sf::Vector2f(x, y));

	healthBar->update(x - sprite->getGlobalBounds().width / 2, y - sprite->getGlobalBounds().height / 2 - 10);
}

std::unique_ptr<Sorcerer> Sorcerer::create(int x, int y)
{
	std::unique_ptr<Sorcerer> ptr(new Sorcerer(x, y));

	return ptr;
}

void Sorcerer::update(const Entity &e, const BoundingBox &box)
{
	moveTowardsPlayer(e);
	move(box);
	if (!dead)
		sprite->update();
	setPosition(x, y);
	healthBar->update(x - sprite->getGlobalBounds().width / 2, y - sprite->getGlobalBounds().height / 2 - 10);
}

void Sorcerer::draw(sf::RenderWindow *window)
{
	window->draw(*sprite);
	healthBar->draw(window);
}

void Sorcerer::move(const BoundingBox &box)
{
	// return or other animations will be played and position will be updated
	if (dead)
		return;

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

	// determine next position
	xdest = x + dx;
	ydest = y + dy;
	tempx = x;
	tempy = y;

	int bx = box.getX();
	int by = box.getY();
	int brickHeight = box.getHeight();
	int brickWidth = box.getWidth();

	if (xdest + width / 2 <= bx - brickWidth / 2)
	{
		currentSide = LEFT_SIDE;
	}
	else if (xdest - width / 2 >= bx + brickWidth / 2)
	{
		currentSide = RIGHT_SIDE;
	}
	else if (ydest - height / 2 >= by + brickHeight / 2)
	{
		currentSide = BOTTOM_SIDE;
	}
	else if (ydest + height / 2 <= by - brickHeight / 2)
	{
		currentSide = TOP_SIDE;
	}

	if (currentSide == LEFT_SIDE || currentSide == RIGHT_SIDE)
	{
		// moving left, check for collision with right side of box
		if (dx < 0)
		{
			if (xdest - width / 2 < (bx + brickWidth / 2) && xdest > (bx) && ydest + height / 2 >(by - brickHeight / 2) && ydest - height / 2 < (by + brickHeight / 2))
			{
				dx = 0;
				teleport(bx - brickWidth / 2 - 20, tempy);
			}
		}
		// moving right, check for collision with left side of box
		if (dx > 0)
		{
			if (xdest + width / 2 > (bx - brickWidth / 2) && xdest < (bx) && ydest + height / 2 >(by - brickHeight / 2) && ydest - height / 2 < (by + brickHeight / 2))
			{
				dx = 0;
				teleport(bx + brickWidth / 2 + 20, tempy);
			}
		}
	}
	if (currentSide == TOP_SIDE || currentSide == BOTTOM_SIDE)
	{
		// moving up, check for collision with bottom side of box
		if (dy < 0)
		{
			if (ydest - height / 2 < (by + brickHeight / 2) && ydest > (by) && xdest + width / 2 >(bx - brickWidth / 2) && xdest - width / 2 < (bx + brickWidth / 2))
			{
				dy = 0;
				teleport(tempx, by - brickHeight / 2 - 20);
			}
		}
		// moving down, check for collision with top side of box
		if (dy > 0)
		{
			if (ydest + height / 2 > (by - brickHeight / 2) && ydest < (by) && xdest + width / 2 >(bx - brickWidth / 2) && xdest - width / 2 < (bx + brickWidth / 2))
			{
				dy = 0;
				teleport(tempx, by + brickHeight / 2 + 20);
			}
		}
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
		}
		// check whether second half of teleport has ended
		if (sprite->hasPlayedOnce() && currentAnimation == TELEPORT_END)
		{
			teleporting = false;
			currentAnimation = STANDING;
			sprite->setFrames(*standing);
		}

		return;
	}

	// sorcerer is moving in any direction
	if (dx < 0 || dx > 0 || dy > 0 || dy < 0)
	{
		if (currentAnimation != WALKING)
		{
			currentAnimation = WALKING;
			sprite->setFrames(*walking);
		}
	}

	// moving left, so make him face left
	if (dx < 0)
		sprite->setScale(-1, 1);
	else if (dx > 0)
		sprite->setScale(1, 1);

	x += dx;
	y += dy;

}

void Sorcerer::teleport(int x, int y)
{
	teleportX = x;
	teleportY = y;
	teleporting = true;
}

Sorcerer::~Sorcerer()
{
	delete walking;
	delete teleportEnd;
	delete teleportStart;
}
