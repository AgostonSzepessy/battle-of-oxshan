#include "PauseState.hpp"

PauseState::PauseState(sf::RenderWindow *window, GameStateManager *gsm) : GameState(window, gsm)
{
	font = new sf::Font;
	if (!font->loadFromFile("res/fonts/arial.ttf"))
	{
		std::cout << "not able to load arial font" << std::endl;
	}
	text = new sf::Text[3];

	background = std::move(Background::create("res/backgrounds/grass.png"));

	// start at the top
	currentChoice = 0;

	setText();
	changeTextColor();
}

PauseState::~PauseState()
{
	delete[] text;
	delete font;
}

/*
* Creates an instance of PauseState and returns a unique_ptr.
*/
std::unique_ptr<PauseState> PauseState::build(sf::RenderWindow *window, GameStateManager *gsm)
{
	std::unique_ptr<PauseState> pauseState(new PauseState(window, gsm));

	return pauseState;
}

void PauseState::update()
{
	handleInput();
	changeTextColor();
}

void PauseState::draw()
{
	window->clear(sf::Color::Black);

	background->draw(window);

	for (int i = 0; i < menuOptions; ++i)
	{
		window->draw(text[i]);
	}

	window->display();
}

void PauseState::handleInput()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
		{
			gsm->quit();
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (text)
			{
				// if the mouse clicks "Resume", then go back to play state
				if (event.mouseButton.button == sf::Mouse::Left && inBounds(text[0].getPosition().x, text[0].getPosition().y,
					text[0].getGlobalBounds().width, text[0].getGlobalBounds().height, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y - 2))
				{
					gsm->popState();
				}
				// if mouse clicks "Restart", then reset play state
				if (event.mouseButton.button == sf::Mouse::Left && inBounds(text[1].getPosition().x, text[1].getPosition().y,
					text[1].getGlobalBounds().width, text[1].getGlobalBounds().height, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y - 2))
				{
					gsm->reset(PlayState::build(window, gsm));
				}
				// if mouse clicks "Exit", then quit the game
				if (event.mouseButton.button == sf::Mouse::Left && inBounds(text[2].getPosition().x, text[2].getPosition().y,
					text[2].getGlobalBounds().width, text[2].getGlobalBounds().height, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y - 2))
				{
					gsm->quit();
				}
			}
		}
		if (event.type == sf::Event::KeyPressed)
		{
			// if enter, or space is pressed, then call select
			if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
			{
				select();
			}
			if (event.key.code == sf::Keyboard::Escape)
			{
				gsm->popState();
			}
			// if s or down arrow is pressed, move down to next button/text
			// if it's greater than menuOptions - 1, then move to top button/text
			if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
			{
				currentChoice++;
				if (currentChoice >= menuOptions)
				{
					currentChoice = menuOptions - 1;
				}
			}
			// if w or up arrow is pressed, move up to next button/text.
			// if it's less than 0, then move to bottom button/text
			if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
			{
				currentChoice--;
				if (currentChoice < 0)
				{
					currentChoice = 0;
				}
			}
		}
	}

	if (text)
	{
		// if hovering over first text/button
		if (inBounds(text[0].getPosition().x, text[0].getPosition().y,
			text[0].getGlobalBounds().width, text[0].getGlobalBounds().height, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
		{
			currentChoice = 0;
		}
		// if hovering over second text/button
		if (inBounds(text[1].getPosition().x, text[1].getPosition().y,
			text[1].getGlobalBounds().width, text[1].getGlobalBounds().height, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
		{
			currentChoice = 1;
		}
		// if hovering over second text/button
		if (inBounds(text[2].getPosition().x, text[2].getPosition().y,
			text[2].getGlobalBounds().width, text[2].getGlobalBounds().height, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
		{
			currentChoice = 2;
		}
	}
}

void PauseState::setText()
{
	// set the font for each sf::Text,
	// set the size, color, and set origin to center
	for (int i = 0; i < menuOptions; ++i)
	{
		text[i].setFont(*font);
		text[i].setCharacterSize(textSize);
		text[i].setColor(textColor);

	}

	// set what the text says and position
	text[0].setString("Resume");
	text[0].setOrigin(text[0].getGlobalBounds().width / 2, text[0].getGlobalBounds().height / 2);
	text[0].setPosition(window->getSize().x / 2, window->getSize().y / 2);

	text[1].setString("Restart");
	text[1].setOrigin(text[1].getGlobalBounds().width / 2, text[1].getGlobalBounds().height / 2);
	text[1].setPosition(window->getSize().x / 2, window->getSize().y / 2 + 30);

	text[2].setString("Exit");
	text[2].setOrigin(text[2].getGlobalBounds().width / 2, text[2].getGlobalBounds().height / 2);
	text[2].setPosition(window->getSize().x / 2, window->getSize().y / 2 + 60);
}

void PauseState::changeTextColor()
{
	// loop through all text, if i equals
	// currentChoice, then set color to a different color
	for (int i = 0; i < menuOptions; ++i)
	{
		if (i == currentChoice)
		{
			text[i].setColor(selectedText);
		}
		else
		{
			text[i].setColor(textColor);
		}
	}
}

void PauseState::select()
{
	// change to PlayState
	if (currentChoice == 0)
	{
		gsm->popState();
	}
	// reset PlayState, so the player can play again
	if (currentChoice == 1)
	{
		gsm->reset(PlayState::build(window, gsm));
	}
	// quit the game
	if (currentChoice == 2)
	{
		gsm->quit();
	}
}

/* check whether the mouse is inside of the text's bounding box
this is to determine which text to highlight based on mouse position
int x2 is mouse.x and int y2 is mouse.y
*/
bool PauseState::inBounds(int x, int y, int width, int height, int x2, int y2)
{
	int hWidth = width / 2;		// half width
	int hHeight = height / 2;

	// check if mouse is inside
	if (x2 < x - hWidth || x2 > x + hWidth || y2 < y - hHeight || y2 > y + hHeight)
	{
		return false;
	}

	return true;
}
