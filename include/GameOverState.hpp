#pragma once

#include <memory>
#include <iostream>
#include <cstdlib>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "GameState.hpp"
#include "GameStateManager.hpp"
#include "Constants.hpp"
#include "PlayState.hpp"
#include "Background.hpp"

/**
 * @brief The GameOverState class This is where the user is taken to
 * once they have died. They are given an option to restart or quit the game.
 * It has all the standard functions that each GameState has.
 */
class GameOverState : public GameState
{
	public:
		/**
		 * @brief build Creates a new std::unique_ptr<GameOverState>
		 * @param window Window to draw everything on
		 * @param gsm GameStateManager that handles state switching, updates, and drawing
		 * @param wave The wave that the user made it to
		 * @return A std::unique_ptr<GameOverState>
		 */
		static std::unique_ptr<GameOverState> build(sf::RenderWindow *window, GameStateManager *gsm, int wave);
		~GameOverState();
		/**
		 * @brief update Updates the GameOverState.
		 */
		void update();
		/**
		 * @brief draw Draws the GameOverState's contents (background, text, etc).
		 */
		void draw();
		/**
		 * @brief handleInput Handles all input, and checks to see if the user signalled
		 * to restart or quit.
		 */
		void handleInput();
	protected:
		
	private:
		GameOverState(sf::RenderWindow *window, GameStateManager *gsm, int wave);
		/**
		 * @brief canPressButtons This restricts the user from pressing any buttons
		 * for 1.5 seconds, because if the user is holding a button when it accesses the
		 * GameOverState, then it's going to restart right away. This prevents it, and allows
		 * the user to decide to quit or keep playing.
		 * @return True if the user can press buttons
		 */
		bool canPressButtons();
		
		sf::Text *message;
		sf::Text *continueText;
		sf::Font *font;
		sf::Clock *c;
		
		/** 
		 * How much time has passed between shots. If it's greater
		 * than delay, the entity can fire.
		 */
		int delay;
		/**
		 * Used for holding the time from when the previous
		 * shot was fired.
		 */
		int prevTime;
		/**
		 * Holds the current time.
		 */
		int currentTime;
		/**
		 * Holds the total time. Each frame, more time gets
		 * added to it until it is greater or equal to delay.
		 * Then it gets reset.
		 */
		int accumulator;
		
		std::unique_ptr<Background> background;
};
