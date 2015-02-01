#include "BoundingBox.hpp"

BoundingBox::BoundingBox(std::vector<std::shared_ptr<Brick>> bricks)
{
	bool horizontal;
	// calculate the center of the brick, x part
	const unsigned size = bricks.size();
	std::vector<int> position;

	for (unsigned i = 0; i < size; ++i)
	{
		position.push_back(bricks[i]->getX());
	}
	std::sort(position.begin(), position.end());

	if (bricks[0]->getX() != bricks[1]->getX())
		horizontal = true;
	else
		horizontal = false;

	if (horizontal)
		width = size * bricks[0]->getWidth();
	else
		width = bricks[0]->getWidth();

	x = (position[0] + position[size - 1]) / 2;

	position.clear();

	// calculate the center of the brick, y part
	for (unsigned i = 0; i < size; ++i)
	{
		position.push_back(bricks[i]->getY());
	}

	std::sort(position.begin(), position.end());

	y = (position[0] + position[size - 1]) / 2;
	if (!horizontal)
		height = size * bricks[0]->getHeight();
	else
		height = bricks[0]->getHeight();

	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}

sf::FloatRect BoundingBox::getLocalBounds() const
{
	return sf::FloatRect(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height));
}

sf::FloatRect BoundingBox::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

int BoundingBox::getHeight() const
{
	return height;
}

int BoundingBox::getWidth() const
{
	return width;
}

int BoundingBox::getX() const
{
	return x;
}

int BoundingBox::getY() const
{
	return y;
}

BoundingBox::~BoundingBox()
{

}
