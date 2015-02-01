#include "HealthUp.hpp"

HealthUp::HealthUp(int x, int y) : Powerup(x, y)
{
	frame = new Frame;
	if (!texture->loadFromFile("res/sprites/powerups/powerup-spritesheet.png"))
	{
		std::cout << "Failed to load healthup image." << std::endl;
	}

	frame->addFrame(sf::IntRect(0, 0, 15, 25));
	sprite->setTexture(*texture);
	sprite->setFrames(*frame);
	sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
}

std::unique_ptr<HealthUp> HealthUp::create(int x, int y)
{
	std::unique_ptr<HealthUp> pointer(new HealthUp(x, y));
	return pointer;
}

void HealthUp::effect(Player &p)
{
	p.addHealthPotion();
}

HealthUp::~HealthUp()
{
	delete frame;
}
