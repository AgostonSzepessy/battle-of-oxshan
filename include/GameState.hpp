#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class GameStateManager;

/**
 * @brief The GameState class Class that is the base for every
 * other GameState. They all must have these functions: update(),
 * to update entities, draw(), to draw everything that needs to be
 * drawn, and handleInput(), to handle all input from the user.
 */
class GameState
{
	
	public:
		/**
		 * @brief GameState Initializes the window, and gsm variables
		 * from the ones that are provided.
		 * @param window Window to draw stuff to.
		 * @param gsm GameStateManager that handles state switching.
		 */
		GameState(sf::RenderWindow *window, GameStateManager *gsm);
		virtual ~GameState();
		/**
		 * @brief update Updates entities, and other things that
		 * need to be updated. Needs to be overriden.
		 */
		virtual void update() = 0;
		/**
		 * @brief draw Draws everything that needs to be drawn.
		 * Needs to be overriden.
		 */
		virtual void draw() = 0;
		/**
		 * @brief handleInput Handles all input from the user.
		 * Needs to be overriden
		 */
		virtual void handleInput() = 0;
		/**
		 * @brief getWindow Gets the window
		 * @return Window to draw stuff to.
		 */
		sf::Window *getWindow();
		
	protected:
		sf::RenderWindow *window;
		GameStateManager *gsm;
		
	private:
		
	
};
