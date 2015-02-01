#include "GameState.hpp"

GameState::GameState(sf::RenderWindow *window, GameStateManager *gsm) : window(window), gsm(gsm)
{

}

GameState::~GameState()
{

}

sf::Window *GameState::getWindow()
{
	return window;
}
