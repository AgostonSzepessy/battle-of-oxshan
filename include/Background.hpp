#pragma once

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Constants.hpp"

/**
 * @brief The Background class Draws the background for the game.
 */
class Background
{
	public:
		/**
		 * @brief create Creates a new Background object and returns an std::unique_ptr<Background>
		 * @param path Path to the background image
		 * @return An std::unique_ptr<Background>
		 */
		static std::unique_ptr<Background> create(std::string path);
		~Background();
		/**
		 * @brief draw Draws the background on the screen.
		 * @param window The window to draw it on.
		 */
		void draw(sf::RenderWindow *window);
		
	protected:
		
		
	private:
		sf::Sprite *sprite;
		sf::Texture *texture;
		/**
		 * @brief Background Creates a Background, and sets it to the center of the screen.
		 * @param path Path to the background image.
		 */
		Background(std::string path);
};
