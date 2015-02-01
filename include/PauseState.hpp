#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "GameState.hpp"
#include "PlayState.hpp"
#include "Background.hpp"

/**
 * @brief The PauseState class This the pause menu.
 * The user can decide to resume, restart or quit.
 */
class PauseState : public GameState
{
	public:
		/**
		 * @brief build Creates a new std::unique_ptr<PauseState>
		 * @param window The window to draw everything on
		 * @param gsm The GameStateManager that handles switching states
		 * @return an std::unique_ptr<PauseState>
		 */
		static std::unique_ptr<PauseState> build(sf::RenderWindow *window, GameStateManager *gsm);
		~PauseState();
		/**
		 * @brief update Calls handleInput(), and changes the text color if
		 * the user has an option selected.
		 */
		void update();
		/**
		 * @brief draw Draws the background, text, and everything else that needs to
		 * be drawn on the screen.
		 */
		void draw();
		/**
		 * @brief handleInput Handles all input from the user.
		 */
		void handleInput();
		
	protected:
	
	private:
		PauseState(sf::RenderWindow *window, GameStateManager *gsm);
		void setText();
		void changeTextColor();
		void select();
		/**
		 * Used for checking whether the mouse coordinates are on the text
		 * when clicking.
		 */
		bool inBounds(int x, int y, int width, int height, int x2, int y2);
		
		const int textSize = 20;
		const int menuOptions = 3;
		int currentChoice = 0;
		const sf::Color textColor = sf::Color::Black;
		const sf::Color selectedText = sf::Color::Blue;
		sf::Font *font;
		sf::Text *text;			// text to store menu options
		int x;					// mouse coordinates
		int y;
		std::unique_ptr<Background> background;
};
