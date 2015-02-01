#include "GameStateManager.hpp"

GameStateManager::GameStateManager()
{
	changingState = false;
	resetting = false;
	popping = false;
}

GameStateManager::~GameStateManager()
{

}

void GameStateManager::quit()
{
	if (!states.empty())
	{
		states.back()->getWindow()->close();
		std::exit(EXIT_SUCCESS);
	}
}

void GameStateManager::reset(std::unique_ptr<GameState> state)
{
	// store the state
	tempState = std::move(state);
	// signal to reset
	resetting = true;
}

void GameStateManager::update()
{
	if (changingState)
	{
		if (!states.empty())
		{
			states.pop_back();
		}
		states.push_back(std::move(tempState));
		changingState = false;
	}
	if (resetting)
	{
		// pop all states, and set the current state to the state parameter
		while (!states.empty())
		{
			states.pop_back();
		}
		states.push_back(std::move(tempState));
		resetting = false;
	}

	if (popping)
	{
		popping = false;
		states.pop_back();
	}

	if (!states.empty())
	{
		states.back()->update();
	}
}

void GameStateManager::draw()
{
	if (!states.empty())
		states.back()->draw();
}

void GameStateManager::changeState(std::unique_ptr<GameState> state)
{
	// use this to tell update() to switch to a different state next time it's called
	changingState = true;
	// store the state
	tempState = std::move(state);
}

void GameStateManager::pushState(std::unique_ptr<GameState> state)
{
	states.push_back(std::move(state));
}

void GameStateManager::popState()
{
	if (!states.empty())
	{
		popping = true;
	}
}
