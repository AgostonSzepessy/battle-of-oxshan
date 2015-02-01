#pragma once

#include <vector>
#include <memory>
#include <utility>
#include <cstdlib>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "GameState.hpp"

class GameStateManager
{	
	public:
		GameStateManager();
		~GameStateManager();
		
		void update();
		void draw();
		
		void pushState(std::unique_ptr<GameState> state);
		void popState();
		void changeState(std::unique_ptr<GameState> state);
		void reset(std::unique_ptr<GameState> state);
		void quit();
		
	protected:
		
	private:	
		std::vector<std::unique_ptr<GameState>> states;
		std::unique_ptr<GameState> tempState;
		
		/**
		 * Used for drawing the previous state. It is used
		 * when the player dies: the field and the enemies are
		 * drawn, but nothing is updated from this state.
		 */
		std::unique_ptr<GameState> prevState;
		
		bool changingState;
		bool resetting;
		bool popping;
};
