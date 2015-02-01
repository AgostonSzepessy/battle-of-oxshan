#include "Entity.hpp"

Entity::Entity()
{
	c = new sf::Clock;
	elapsed = new sf::Time;
	last = new sf::Time;
	delay = 1000;
	sprite = new AnimatedSprite;
	texture = new sf::Texture;
	prevTime = c->getElapsedTime().asMilliseconds();
	currentTime = 0;
	accumulator = 0;
}

bool Entity::checkCollision(const Entity &e)
{
	if (sprite->getGlobalBounds().intersects(e.getSprite().getGlobalBounds()))
	{
		return true;
	}
	return false;
}

int Entity::getWidth() const
{
	return width;
}

int Entity::getHeight() const
{
	return height;
}

bool Entity::canFire()
{
	currentTime = c->getElapsedTime().asMilliseconds();
	accumulator += currentTime - prevTime;
	prevTime = currentTime;
	if (accumulator > delay)
	{
		accumulator = 0;
		return true;
	}
	return false;
}

void Entity::setPosition(int x, int y)
{
	sprite->setPosition(sf::Vector2f(x, y));
}

void Entity::checkBounds()
{
	if (x + width / 2 >= WIDTH)
		x = WIDTH - width / 2;
	if (x - width / 2 <= 0)
		x = 0 + width / 2;
	if (y - height / 2 <= 0)
		y = 0 + height / 2;
	if (y + height / 2 >= HEIGHT)
		y = HEIGHT - height / 2;
}

sf::Vector2f Entity::getPosition()
{
	return sprite->getPosition();
}

AnimatedSprite Entity::getSprite() const
{
	return *sprite;
}

int Entity::getX() const
{
	return x;
}

int Entity::getY() const
{
	return y;
}


void Entity::checkBrickCollision(const BoundingBox &box)
{
	// determine next position
	xdest = x + dx;
	ydest = y + dy;
	// use tempx so the original x value doesn't get modified
	tempx = x;
	tempy = y;


	// get box position, width etc for collision detection
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
				tempx = bx + brickWidth / 2 + width / 2;
			}
		}
		// moving right, check for collision with left side of box
		if (dx > 0)
		{
			if (xdest + width / 2 > (bx - brickWidth / 2) && xdest < (bx) && ydest + height / 2 >(by - brickHeight / 2) && ydest - height / 2 < (by + brickHeight / 2))
			{
				dx = 0;
				tempx = bx - brickWidth / 2 - width / 2;
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
				tempy = by + brickHeight / 2 + height / 2;
			}
		}
		// moving down, check for collision with top side of box
		if (dy > 0)
		{
			if (ydest + height / 2 > (by - brickHeight / 2) && ydest < (by) && xdest + width / 2 >(bx - brickWidth / 2) && xdest - width / 2 < (bx + brickWidth / 2))
			{
				dy = 0;
				tempy = by - brickHeight / 2 - height / 2;
			}
		}
	}
}

bool Entity::checkCollision(const BoundingBox &box)
{
	int bx = box.getX();
	int by = box.getY();
	int bWidth = box.getWidth() / 2;
	int bHeight = box.getHeight() / 2;

	if (x < bx - bWidth || x > bx + bWidth || y < by - bHeight || y > by + bHeight)
		return false;
	return true;
}

Entity::~Entity()
{
	delete c;
	delete elapsed;
	delete last;
	sprite->cleanUp();
	delete sprite;
	delete texture;
}
