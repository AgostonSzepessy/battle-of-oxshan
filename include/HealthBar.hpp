#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/**
 * @brief The HealthBar class Encapsulates a health bar. The green
 * shows how much health entities have left, and the red helps show
 * how much they lost.
 */
class HealthBar
{
	public:
		/**
		 * @brief HealthBar Creates a new HealthBar, and sets its position
		 * @param x The x position of the HealthBar
		 * @param y The y position of the HealthBar
		 */
		HealthBar(int x, int y);
		~HealthBar();
		/**
		 * @brief update Sets the x and y position of the HealthBar
		 * @param x The x position of the HealthBar
		 * @param y The y position of the HealthBar
		 */
		void update(int x, int y);
		/**
		 * @brief draw Draws the red rectangle, and then the green
		 * rectangle over top of it. In other words, it draws the HealthBar.
		 * @param window
		 */
		void draw(sf::RenderWindow *window);
		/**
		 * @brief setHealth Sets how much health the HealthBar should show.
		 * @param health The amount of health to show
		 */
		void setHealth(int health);
		/**
		 * @brief isDead Checks if the owner of the HealthBar is dead.
		 * @return True if the owner is dead.
		 */
		bool isDead();
		
	protected:
	
	private:
		sf::RectangleShape *remainderBar;		// how much health the entity has remaining
		sf::RectangleShape *deadBar;			// this is the background of the health bar
		const int size = 100;							// width of the health bar & maximum health
		int remaining;							// width of how much remaining
		int height;
};
