#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "Player.hpp"

class Powerup : public Entity
{
	public:
		virtual ~Powerup();
		/**
		 * @brief The effect that the powerup has on the player. This
		 * has to be overridden.
		 * @param p The player
		 */
		virtual void effect(Player &p) = 0;
		/**
		 * @brief Draw the powerup.
		 * @param window The window to draw the Powerup on.
		 */
		void draw(sf::RenderWindow *window);
	protected:
		/**
		 * @brief Creates a Powerup at x, y.
		 * @param x The x position
		 * @param y The y position
		 */
		Powerup(int x, int y);
	private:
		
};
