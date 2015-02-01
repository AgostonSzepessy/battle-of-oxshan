#include "Frame.hpp"

Frame::Frame()
{
	delay = -1;
}

void Frame::setDelay(double d)
{
	delay = d;
}

void Frame::addFrame(const sf::IntRect &rect)
{
	frames.push_back(rect);
}

int Frame::getDelay() const
{
	return delay;
}

std::vector<sf::IntRect> Frame::getFrames() const
{
	return frames;
}
