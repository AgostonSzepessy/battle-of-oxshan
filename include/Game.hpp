#pragma once

#include <iostream>
#include <climits>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "GameStateManager.hpp"
#include "MenuState.hpp"
#include "PlayState.hpp"

/**
 * @brief The Game class Main class of the game. This is the class
 * that calls all the update, and draw functions. It sets up the game.
 */
class Game
{
	public:	
		/**
		 * @brief Game Creates a new Game object. It sets up the window,
		 * disables v-sync so framerate isn't restricted, and initializes the
		 * accumulator.
		 */
		Game();
		~Game();
		/**
		 * @brief run Starts the game and runs it.
		 */
		void run();
		
	protected:
		
	private:
		sf::RenderWindow window;

		void update();
		void draw();
		void init();
		
		int FPS = 60;
		const sf::Time STEP = sf::milliseconds(1000/FPS);
		sf::Int64 accumulator;
		//int averageFPS; // used for debugging
		sf::Clock c;
		//sf::Thread thread;
		GameStateManager gsm;
};
