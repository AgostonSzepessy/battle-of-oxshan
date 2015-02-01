#include "HealthBar.hpp"

HealthBar::HealthBar(int x, int y)
{
	remaining = size;
	height = 10;
	deadBar = new sf::RectangleShape;
	remainderBar = new sf::RectangleShape;

	deadBar->setPosition(sf::Vector2f(x, y));
	remainderBar->setPosition(sf::Vector2f(x, y));
	deadBar->setFillColor(sf::Color::Red);
	remainderBar->setFillColor(sf::Color::Yellow);
}

HealthBar::~HealthBar()
{
	delete deadBar;
	delete remainderBar;
}

void HealthBar::update(int x, int y)
{
	deadBar->setPosition(sf::Vector2f(x, y));
	remainderBar->setPosition(sf::Vector2f(x, y));

	deadBar->setSize(sf::Vector2f(size / 2, height));
	remainderBar->setSize(sf::Vector2f(remaining / 2, height));
}

void HealthBar::draw(sf::RenderWindow *window)
{
	window->draw(*deadBar);
	window->draw(*remainderBar);
}

void HealthBar::setHealth(int health)
{
	remaining = health;
}

bool HealthBar::isDead()
{
	return remaining > 0;
}
