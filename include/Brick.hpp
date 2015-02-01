#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <memory>
#include <iostream>

#include "Frame.hpp"
#include "AnimatedSprite.hpp"

/**
 * @brief The Brick class This class encapsulates a brick object. It
 * contains methods to create them, draw them, and to get their properties
 * like position, etc.
 */
class Brick
{
	public:
		/**
		 * @brief create Creates a new Brick object, sets its position, and returns an
		 * std::unique_ptr<Brick> pointing to it.
		 * @param x X position of the brick
		 * @param y Y position of the brick
		 * @return An std::unique_ptr<Brick> pointing to the Brick object created.
		 */
		static std::shared_ptr<Brick> create(int x, int y);
		~Brick();
		/**
		 * @brief draw Draws the brick on the window.
		 * @param window Window to draw it on.
		 */
		void draw(sf::RenderWindow *window);
		/**
		 * @brief getX Gets the x position of the brick
		 * @return The x position of the brick
		 */
		int getX() const;
		/**
		 * @brief getY Gets the y position of the brick.
		 * @return The y position of the brick
		 */
		int getY() const;
		/**
		 * @brief getWidth Gets the width of the brick.
		 * @return The width of the brick
		 */
		int getWidth() const;
		/**
		 * @brief getHeight Gets the height of the brick
		 * @return The height of the brick
		 */
		int getHeight() const;
		/**
		 * @brief getSprite Gets the brick sprite
		 * @return The brick sprite
		 */
		AnimatedSprite getSprite() const;
		
	protected:
	
	private:
		Brick(int x, int y);
		void setPosition(int x, int y);
		
		double x;
		double y;
		int height;
		int width;
		
		Frame *frame;
		AnimatedSprite *sprite;
		sf::Texture *texture;
};
