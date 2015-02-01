#include "Background.hpp"

Background::Background(std::string path)
{
	texture = new sf::Texture;

	if (!texture->loadFromFile(path))
	{
		std::cout << "unable to load " << path << std::endl;
	}

	sprite = new sf::Sprite;
	sprite->setTexture(*texture);
	sprite->setPosition(0, 0);
}

std::unique_ptr<Background> Background::create(std::string path)
{
	std::unique_ptr<Background> b(new Background(path));
	return b;
}

void Background::draw(sf::RenderWindow *window)
{
	window->draw(*sprite);
}

Background::~Background()
{
	delete sprite;
	delete texture;
}