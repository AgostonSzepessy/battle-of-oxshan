#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Brick.hpp"

/**
 * @brief The BoundingBox class Used for detecting collision with multiple bricks. It makes one big bounding box around
 * a row of bricks and that box is used for collision detection.
 * For example, if there are 3 bricks going downwards, this class creates a large box around it
 * and that box is used for collision.
 */
class BoundingBox : public sf::Transformable
{
	public:
		/**
		 * @brief BoundingBox Determines how many bricks there are, and creates
		 * a bounding box around them.
		 * @param bricks The bricks that the BoundingBox is to be created around.
		 */
		BoundingBox(std::vector<std::shared_ptr<Brick>> bricks);
		~BoundingBox();
		/**
		 * @brief getHeight Returns the height.
		 * @return Height of BoundingBox
		 */
		int getHeight() const;
		/**
		 * @brief getWidth Returns the width of the BoundingBox
		 * @return Width of BoundingBox
		 */
		int getWidth() const;
		/**
		 * @brief getX Returns x position of BoundingBox
		 * @return X position of BoundingBox
		 */
		int getX() const;
		/**
		 * @brief getY Returns y position of BoundingBox
		 * @return Y position of BoundingBox
		 */
		int getY() const;
		/**
		 * @brief getLocalBounds Returns the bounding box of the BoundingBox object without
		 * any transformations applied to it.
		 * @return BoundingBox without any transformations applied
		 */
		sf::FloatRect getLocalBounds() const;
		/**
		 * @brief getGlobalBounds Returns the bounding box of the BoundingBox object with all
		 * transformations applied to it.
		 * @return BoundingBox with all transformations applied.
		 */
		sf::FloatRect getGlobalBounds() const;
		
	protected:
	
	private:
		/**
		 * @brief x X position
		 */
		int x;
		/**
		 * @brief y Y position
		 */
		int y;
		/**
		 * @brief width Width of BoundingBox
		 */
		int width;
		/**
		 * @brief height Height of BoundingBox
		 */
		int height;
		
};
