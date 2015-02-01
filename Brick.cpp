#include "Brick.hpp"

Brick::Brick(int x, int y)
{
	this->x = x;
	this->y = y;

	sprite = new AnimatedSprite;
	texture = new sf::Texture;
	frame = new Frame;

	frame->addFrame(sf::IntRect(0, 0, 64, 64));
	if (!texture->loadFromFile("res/sprites/brick.png"))
	{
		std::cout << "unable to load brick file" << std::endl;
	}

	height = 64;
	width = 64;

	sprite->setTexture(*texture);
	sprite->setFrames(*frame);
	sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
	setPosition(x, y);
}

int Brick::getHeight() const
{
	return height;
}

int Brick::getWidth() const
{
	return width;
}

void Brick::setPosition(int x, int y)
{
	sprite->setPosition(sf::Vector2f(x, y));
}

std::shared_ptr<Brick> Brick::create(int x, int y)
{
	std::shared_ptr<Brick> brick(new Brick(x, y));

	return brick;
}

void Brick::draw(sf::RenderWindow *window)
{
	window->draw(*sprite);
}

int Brick::getX() const
{
	return static_cast<int>(x);
}

int Brick::getY() const
{
	return static_cast<int>(y);
}

AnimatedSprite Brick::getSprite() const
{
	return *sprite;
}

Brick::~Brick()
{
	sprite->cleanUp();
	delete frame;
	delete texture;
	delete sprite;
}
