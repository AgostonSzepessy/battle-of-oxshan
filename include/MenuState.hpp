#pragma once

#include <iostream>
#include <cstdlib>
#include <memory>
#include <new>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "GameStateManager.hpp"
#include "GameState.hpp"
#include "PlayState.hpp"
#include "Background.hpp"

/**
 * @brief The MenuState class The GameState that is the
 * main menu. The user can choose to start the game or quit.
 */
class MenuState : public GameState
{
	public:
		/**
		 * @brief build Creates a new std::unique_ptr<MenuState>
		 * @param window The window to draw everything on
		 * @param gsm The GameStateManager that handles switching
		 * to different GameStates
		 * @return An std::unique_ptr<MenuState>
		 */
		static std::unique_ptr<MenuState> build(sf::RenderWindow *window, GameStateManager *gsm);
		~MenuState();
		/**
		 * @brief update Calls handleInput(), and changes the text colour for
		 * the option that the user has selected.
		 */
		void update();
		/**
		 * @brief draw Draws the background and all text on the screen.
		 */
		void draw();
		/**
		 * @brief handleInput Handles all input that the user gives.
		 */
		void handleInput();


		
	protected:
		
		
	private:
		MenuState(sf::RenderWindow *window, GameStateManager *gsm);
		/**
		* Set the text attributes like font, size, etc.
		*/
		void setText();
		/**
		* Initialize the text and check for failures.
		*/ 
		void createText();
		/**
		* Change the color of the text based
		* on the user's input.
		*/
		void changeTextColor();
		/**
		* Changes states based on the option selected.
		*/
		void select();
		/**
		 * Used for checking whether the mouse coordinates are on the text
		 * when clicking.
		 */
		bool inBounds(int x, int y, int width, int height, int x2, int y2);
		
		/**
		 * The size of the text that is displayed.
		 */
		const int textSize = 20;
		/**
		 * The number of menu options in the menu.
		 */
		const int menuOptions = 2;
		/**
		 * The option text that the player has selected. Increases from
		 * top to bottom. The first is 0. This variable is also used to determine
		 * which color the text should be.
		 */
		int currentChoice = 0;
		/**
		 * Normal text color is black.
		 */
		const sf::Color textColor = sf::Color::Black;
		/**
		 * Selected text color is blue.
		 */
		const sf::Color selectedText = sf::Color::Blue;
		sf::Font *font;
		/**
		 * Text to store the menu options in. This is an array.
		 */
		sf::Text *text;
		/**
		 * @brief title Title of the game.
		 */
		sf::Text *title;
		/**
		 * Mouse x coordinate.
		 */
		int x;
		/**
		 * Mouse y coordinate.
		 */
		int y;
		/**
		 * The background of the MenuState.
		 */
		std::unique_ptr<Background> background;
		
		
};
