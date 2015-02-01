#include "Powerup.hpp"

Powerup::Powerup(int x, int y)
{
	// set x & y position
	this->x = x;
	this->y = y;

	sprite->setPosition(x, y);
}

void Powerup::draw(sf::RenderWindow *window)
{
	window->draw(*sprite);
}

Powerup::~Powerup()
{

}
