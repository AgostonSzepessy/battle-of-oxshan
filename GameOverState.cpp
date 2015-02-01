#include "GameOverState.hpp"

GameOverState::GameOverState(sf::RenderWindow *window, GameStateManager *gsm, int wave) : GameState(window, gsm)
{
	message = new sf::Text;
	continueText = new sf::Text;
	font = new sf::Font;
	c = new sf::Clock;
	background = std::move(Background::create("res/backgrounds/grass.png"));

	accumulator = 0;
	prevTime = c->getElapsedTime().asMilliseconds();

	if (!font->loadFromFile("res/fonts/arial.ttf"))
	{
		std::cout << "could not load font: arial.ttf" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	message->setFont(*font);
	message->setColor(sf::Color::Black);
	message->setString("Good job! You made it to wave " + std::to_string(wave) + "!");
	message->setOrigin(message->getGlobalBounds().width / 2, message->getGlobalBounds().height / 2);
	message->setPosition(WIDTH / 2, HEIGHT / 2);

	continueText->setFont(*font);
	continueText->setColor(sf::Color::Black);
	continueText->setString("Press Escape to quit, and any other key to restart.");
	continueText->setOrigin(continueText->getGlobalBounds().width / 2, continueText->getGlobalBounds().height / 2);
	continueText->setPosition(WIDTH / 2 + 25, HEIGHT / 2 + 25);

	delay = 1500;
}

std::unique_ptr<GameOverState> GameOverState::build(sf::RenderWindow *window, GameStateManager *gsm, int wave)
{
	std::unique_ptr<GameOverState> p(new GameOverState(window, gsm, wave));
	return p;
}

GameOverState::~GameOverState()
{
	delete message;
	delete continueText;
	delete font;
	delete c;
}

void GameOverState::handleInput()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (canPressButtons())
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
				gsm->quit();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					gsm->quit();
				else
					gsm->reset(PlayState::build(window, gsm));
			}
			if (event.type == sf::Event::MouseButtonPressed)
				gsm->reset(PlayState::build(window, gsm));
		}
	}
}

void GameOverState::update()
{
	handleInput();
}

void GameOverState::draw()
{
	window->clear(sf::Color::Black);
	background->draw(window);
	window->draw(*message);
	window->draw(*continueText);
	window->display();
}

bool GameOverState::canPressButtons()
{

	currentTime = c->getElapsedTime().asMilliseconds();
	accumulator += currentTime - prevTime;
	prevTime = currentTime;
	if (accumulator > delay)
	{
		return true;
	}
	return false;
}
