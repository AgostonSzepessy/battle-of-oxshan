#pragma once

#include <iostream>
#include <memory>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Entity.hpp"
#include "Constants.hpp"
#include "Frame.hpp"

/**
 * @brief The Bullet class Encapsulates a bullet. It has functions that an Entity
 * has and ones that relate specifically to it, like checking whether it's out of
 * bounds, or getting the damage done by it.
 */
class Bullet : public Entity
{
	public:
		virtual ~Bullet();
		/**
		 * @brief update Updates the bullet by moving it to it's new
		 * position.
		 */
		void update();
		/**
		 * @brief draw Draws the bullet on the window
		 * @param window Window to draw it on
		 */
		void draw(sf::RenderWindow *window);
		/**
		 * @brief outOfBounds Checks if the bullet is out of bounds.
		 * @return True if it's out of bounds
		 */
		bool outOfBounds();
		/**
		 * @brief getDamage Gets the damage that the bullet deals.
		 * @return Damage of the bullet
		 */
		int getDamage();
		/**
		 * @brief setDamage Sets the damage that the bullet deals.
		 * @param d Bullet damage
		 */
		void setDamage(int d);
		
	protected:
		/**
		 * @brief Bullet Creates a Bullet object
		 * @param entityPositionX The x position of the entity that's firing the bullet
		 * @param entityPositionY The y position of the entity that's firing the bullet
		 * @param mousePositionX The x position of the mouse or where the bullet will go
		 * @param mousePositionY The y position of the mouse or where the bullet will go
		 * @param path Path to the texture
		 * @param x1 The x start position of the texture on the image
		 * @param y1 The y start position of the texture on the image
		 * @param xoffset The x offset that gets added to the start position to calculate the x
		 * end position on the image for the texture
		 * @param yoffset The y offset that gets added to the start position to calculate the y
		 * end position on the image for the texture
		 */
		Bullet(int entityPositionX, int entityPositionY, int mousePositionX, int mousePositionY, std::string path, int x1, int y1, int xoffset, int yoffset);
		
		int damage;
		int speed;
		
	private:
		
		void moveBullet();
		void setPosition(int x, int y);
		
		Frame *moving;
};
