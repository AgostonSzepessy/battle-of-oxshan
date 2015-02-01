#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite() : texture(NULL)
{
	c = new sf::Clock;
	startTime = new sf::Time;
	elapsedTime = new sf::Time;
}

AnimatedSprite::~AnimatedSprite()
{

}

void AnimatedSprite::cleanUp()
{
	delete c;
	delete startTime;
	delete elapsedTime;
}

void AnimatedSprite::setFrames(const Frame &f)
{
	// erase all frames, and set new ones
	frames.erase(frames.begin(), frames.end());
	frames.clear();
	frames = f.getFrames();
	// the frames start at 0
	currentFrame = 0;
	// reset timer
	*startTime = c->getElapsedTime();
	*elapsedTime = sf::milliseconds(0);
	// has not played once
	playedOnce = false;
	delay = f.getDelay();
	setFrame(currentFrame);
}

void AnimatedSprite::update()
{
	// no need to update if it's -1
	// some entities don't need to be updated
	if (delay <= -1)
		return;

	// add time
	*elapsedTime += c->getElapsedTime() - *startTime;

	// if time elapsed is greater than delay, go to next frame
	if (elapsedTime->asMilliseconds() > delay)
	{
		setFrame(currentFrame);
		currentFrame++;
		*elapsedTime = sf::milliseconds(0);
		*startTime = c->getElapsedTime();
	}
	// if at last frame, reset frames, and signal that animation played once
	if (currentFrame == frames.size())
	{
		currentFrame = 0;
		playedOnce = true;
		*elapsedTime = sf::milliseconds(0);
	}
	*startTime = c->getElapsedTime();
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = texture;
	target.draw(vertices, 4, sf::Quads, states);
}

void AnimatedSprite::setFrame(unsigned u_frame)
{
	// get the IntRect for the current frame
	sf::IntRect frame = frames[u_frame];

	// get height and width
	float height = static_cast<float>(frame.height);
	float width = static_cast<float>(frame.width);

	// set the position for the vertices
	vertices[0].position = sf::Vector2f(0.0f, 0.0f);
	vertices[1].position = sf::Vector2f(0.0f, height);
	vertices[2].position = sf::Vector2f(width, height);
	vertices[3].position = sf::Vector2f(frame.width, 0.0f);

	// get the texture size
	float left = static_cast<float>(frame.left) + 0.0001f;
	float right = left + width;
	float top = static_cast<float>(frame.top);
	float bottom = top + height;

	// set the texture coordinates to use from the image
	vertices[0].texCoords = sf::Vector2f(left, top);
	vertices[1].texCoords = sf::Vector2f(left, bottom);
	vertices[2].texCoords = sf::Vector2f(right, bottom);
	vertices[3].texCoords = sf::Vector2f(right, top);
}

void AnimatedSprite::setTexture(sf::Texture &text)
{
	// set the texture
	texture = &text;
	if (texture == NULL)
	{
		std::cout << "AnimatedSprite texture is NULL" << std::endl;
	}
}

bool AnimatedSprite::hasPlayedOnce()
{
	return playedOnce;
}

sf::FloatRect AnimatedSprite::getLocalBounds() const
{
	// get current frame
	sf::IntRect rect = frames[currentFrame];

	// get height and width
	float width = static_cast<float>(rect.width);
	float height = static_cast<float>(rect.height);

	// return bounding box
	return sf::FloatRect(0.0f, 0.0f, width, height);
}

sf::FloatRect AnimatedSprite::getGlobalBounds() const
{
	// return bounding box with transformations
	return getTransform().transformRect(getLocalBounds());
}
