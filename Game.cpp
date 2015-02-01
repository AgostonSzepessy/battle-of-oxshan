#include "Game.hpp"

Game::Game()
{
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Game");
	window.setVerticalSyncEnabled(false);
	accumulator = 0;
}

void Game::run()
{
	init();

	int prevTime = c.getElapsedTime().asMilliseconds();
	int currentTime = 0;

	while (window.isOpen())
	{
		currentTime = c.getElapsedTime().asMilliseconds();
		accumulator += currentTime - prevTime;
		prevTime = currentTime;


		while (accumulator >= STEP.asMilliseconds())
		{
			accumulator -= STEP.asMilliseconds();
			update();
			draw();
		}
	}
}

void Game::init()
{
	gsm.changeState(MenuState::build(&window, &gsm));
}

void Game::update()
{
	// check if window is open or get a segfault
	if (window.isOpen())
		gsm.update();
}

void Game::draw()
{
	// check if window is open or get a segfault
	if (window.isOpen())
		gsm.draw();
}

Game::~Game()
{
}
