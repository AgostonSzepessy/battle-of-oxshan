#include "InvincibilityUp.hpp"

InvincibilityUp::InvincibilityUp(int x, int y) : Powerup(x, y)
{
	frame = new Frame;
	if (!texture->loadFromFile("res/sprites/powerups/powerup-spritesheet.png"))
	{
		std::cout << "Failed to load InvincibilityUp image." << std::endl;
	}

	frame->addFrame(sf::IntRect(15, 0, 15, 25));
	sprite->setTexture(*texture);
	sprite->setFrames(*frame);
	sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
}

std::unique_ptr<InvincibilityUp> InvincibilityUp::create(int x, int y)
{
	std::unique_ptr<InvincibilityUp> pointer(new InvincibilityUp(x, y));
	return pointer;
}

InvincibilityUp::~InvincibilityUp()
{
	delete frame;
}

void InvincibilityUp::effect(Player &p)
{
	p.addInvincibilityPotion();
}