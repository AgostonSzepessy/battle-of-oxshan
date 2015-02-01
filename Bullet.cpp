#include "Bullet.hpp"

Bullet::Bullet(int entityPositionX, int entityPositionY, int mousePositionX, int mousePositionY, std::string path, int x1, int y1, int xoffset, int yoffset) : speed(6)
{
	// get vector between entity and mouse position
	int distanceX = mousePositionX - entityPositionX;
	int distanceY = mousePositionY - entityPositionY;

	// get magnitued of vector
	float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

	// normalize vector and set dy & dx
	dx = speed * static_cast<double>(distanceX) / distance;
	dy = speed * static_cast<double>(distanceY) / distance;

	x = entityPositionX;
	y = entityPositionY;

	damage = 5;

	// 	texture = new sf::Texture();

	if (!texture->loadFromFile(path))
	{
		std::cout << "not able to load " << path << std::endl;
	}

	// 	sprite = new AnimatedSprite();
	moving = new Frame;
	sprite->setTexture(*texture);
	moving->addFrame(sf::IntRect(x1, y1, xoffset, yoffset));
	sprite->setFrames(*moving);
	sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);

}

void Bullet::moveBullet()
{
	x += dx;
	y += dy;

}

void Bullet::update()
{
	moveBullet();
	setPosition(x, y);
}

void Bullet::draw(sf::RenderWindow *window)
{
	window->draw(*sprite);
}

void Bullet::setPosition(int x, int y)
{
	sprite->setPosition(sf::Vector2f(x, y));
}

bool Bullet::outOfBounds()
{
	// if bullet exceeds bounds
	if (x > WIDTH || y > HEIGHT || x < -1 || y < 0)
	{
		return true;
	}
	return false;
}

int Bullet::getDamage()
{
	return damage;
}

void Bullet::setDamage(int d)
{
	damage = d;
}

Bullet::~Bullet()
{
	delete moving;
}
