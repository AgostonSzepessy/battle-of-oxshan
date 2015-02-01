#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Frame.hpp"

/**
 * @brief The AnimatedSprite class
 * This class takes Frames and animates them. It does this by looking
 * at the texture of an entity, and using the Frames to see which part
 * of the image to select and display on the screen.
 */
class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
	public:
		/**
		 * Sets up the AnimatedSprite class by initializing everything that
		 * needs to get initialized.
		 */
		AnimatedSprite();
		/**
		 * Destructor.
		 */
		~AnimatedSprite();
		/**
		 * @brief setFrames Sets the frames vector equal to the paramater, and starts the timer.
		 * @param f The frames to copy
		 */
		void setFrames(const Frame &f);
		/**
		 * @brief setDelay Sets the delay between frames.
		 * @param delay The delay between frames
		 */
		void setDelay(int delay);
		/**
		 * @brief setTexture Sets the texture for the sprite.
		 * @param texture The texture that it is going to be set to.
		 */
		void setTexture(sf::Texture &texture);
		/**
		 * @brief update Updates the image for the sprite.
		 */
		void update();
		/**
		 * @brief getLocalBounds Returns the bounding box of the sprite without any transformations
		 * applied to it.
		 */
		sf::FloatRect getLocalBounds() const;
		/**
		 * @brief getGlobalBounds Returns the bounding box of the sprite with all transformations applied
		 * to it.
		 */
		sf::FloatRect getGlobalBounds() const;
		/**
		 * @brief cleanUp Cleans up the AnimatedSprite by deleting everything that has been allocated.
		 */
		void cleanUp();
		/**
		 * @brief hasPlayedOnce Checks if all the frames have been looped through.
		 * @return true if all have been looped through
		 */
		bool hasPlayedOnce();
		
	protected:
		
	private:
		/**
		 * @brief draw Draws the target to a render target.
		 * @param target The target to draw it to.
		 * @param states The states
		 */
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		/**
		 * @brief setFrame Sets the frame to the specified number.
		 * @param frame The frame to set the currentFrame to.
		 */
		void setFrame(unsigned frame);

		/**
		 * The vector that holds the frames to be animated.
		 */
		std::vector<sf::IntRect> frames;
		/**
		 * The clock that does the timing for the animation.
		 */
		sf::Clock *c;
		/**
		 * The time when the clock started.
		 */
		sf::Time *startTime;
		/**
		 * The time elapsed since the last frame.
		 */
		sf::Time *elapsedTime;
		/**
		 * The Vertex array used for updating the animation.
		 */
		sf::Vertex vertices[4];
		/**
		 * The texture for the sprite.
		 */
		sf::Texture *texture;
		/**
		 * The current frame. It must be greater than 0.
		 */
		unsigned currentFrame;
		/**
		 * True if it has played once.
		 */
		bool playedOnce;
		/**
		 * Delay in milliseconds between frames.
		 */
		int delay;
};
