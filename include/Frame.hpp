#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>

/**
 * A class that .
 */
/**
 * @brief The Frame class Contains the frames in a vector that are needed for an AnimatedSprite
 * and the delay between each frame. A frame is an sf::IntRect and the
 * AnimatedSprite uses that to find the subimage
 */
class Frame
{
	public:
		/**
		 * @brief Frame Creates a new Frame
		 */
		Frame();
		/**
		 * @brief setDelay Sets the delay between the frames
		 * @param d The delay between frames
		 */
		void setDelay(double d);
		/**
		 * @brief addFrame Adds a frame to the back of the vector
		 * @param rect The Frame to add
		 */
		void addFrame(const sf::IntRect &rect);
		/**
		 * @brief getFrames Returns a vector that contains all the frames
		 * that have been added.
		 * @return A vector with all the frames
		 */
		std::vector<sf::IntRect> getFrames() const;
		/**
		 * @brief getDelay Gets the delay between frames.
		 * @return Delay between frames
		 */
		int getDelay() const;
	
	protected:
	
	private:
		std::vector<sf::IntRect> frames;
		int delay;
		int height;
		int width;
};
