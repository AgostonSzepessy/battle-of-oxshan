#include "MenuState.hpp"

MenuState::MenuState(sf::RenderWindow *window, GameStateManager *gsm) : GameState(window, gsm)
{
	createText();
	setText();
	x = text[0].getPosition().x;
	y = text[0].getPosition().y;
	currentChoice = 0;
	changeTextColor();

	background = std::move(Background::create("res/backgrounds/grass.png"));
}

MenuState::~MenuState()
{
	delete[] text;
	delete title;
	delete font;
}

std::unique_ptr<MenuState> MenuState::build(sf::RenderWindow *window, GameStateManager *gsm)
{

	std::unique_ptr<MenuState> menuState(new MenuState(window, gsm));

	return menuState;
}

void MenuState::update()
{
	handleInput();
	changeTextColor();
}

void MenuState::draw()
{
	window->clear(sf::Color::Black);

	background->draw(window);

	window->draw(*title);

	for (int i = 0; i < menuOptions; ++i)
	{
		window->draw(text[i]);
	}

	window->display();
}

void MenuState::handleInput()
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
			// if the player clicks the mouse while it's on the first option, switch to PlayState
			if (event.mouseButton.button == sf::Mouse::Left && inBounds(text[0].getPosition().x, text[0].getPosition().y,
				text[0].getGlobalBounds().width, text[0].getGlobalBounds().height, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y - 2))
			{
				gsm->changeState(PlayState::build(window, gsm));
			}
			// if the player clicks quit, then quit
			if (event.mouseButton.button == sf::Mouse::Left && inBounds(text[1].getPosition().x, text[1].getPosition().y,
				text[1].getGlobalBounds().width, text[1].getGlobalBounds().height, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y - 2))
			{
				gsm->quit();
			}
		}
		if (event.type == sf::Event::KeyPressed)
		{
			// if the player presses enter or space, do what that option does
			if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
			{
				select();
			}
			// move the choice down
			if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
			{
				currentChoice++;
				if (currentChoice >= menuOptions)
				{
					currentChoice = menuOptions - 1;
				}
			}
			// move the choice up
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
	// if mouse hoves over text set its color
	if (inBounds(text[0].getPosition().x, text[0].getPosition().y,
		text[0].getGlobalBounds().width, text[0].getGlobalBounds().height, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
	{
		currentChoice = 0;
	}
	// if mouse hoves over text set its color
	if (inBounds(text[1].getPosition().x, text[1].getPosition().y,
		text[1].getGlobalBounds().width, text[1].getGlobalBounds().height, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
	{
		currentChoice = 1;
	}

}

void MenuState::createText()
{
	font = new sf::Font;
	text = new sf::Text[menuOptions];
	title = new sf::Text;

	if (!font->loadFromFile("res/fonts/arial.ttf"))
	{
		std::cout << "could not load font: arial.ttf" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void MenuState::setText()
{
	for (int i = 0; i < menuOptions; ++i)
	{
		text[i].setFont(*font);
		text[i].setCharacterSize(textSize);
		text[i].setColor(textColor);

	}

	text[0].setString("Play");
	text[0].setPosition(window->getSize().x / 2, window->getSize().y / 2);
	text[0].setOrigin(text[0].getGlobalBounds().width / 2, text[0].getGlobalBounds().height / 2);

	text[1].setString("Exit");
	text[1].setPosition(window->getSize().x / 2, window->getSize().y / 2 + 30);
	text[1].setOrigin(text[1].getGlobalBounds().width / 2, text[1].getGlobalBounds().height / 2);

	title->setString("The Battle of Oxshan");
	title->setCharacterSize(20);
	title->setOrigin(title->getGlobalBounds().width / 2, title->getGlobalBounds().height / 2);
	title->setPosition(window->getSize().x / 2 - 90, window->getSize().y /2 - 75);
	title->setFont(*font);
	title->setColor(textColor);

}

void MenuState::changeTextColor()
{
	// loop through text and set the color
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

void MenuState::select()
{
	if (currentChoice == 0)
	{
		gsm->changeState(PlayState::build(window, gsm));
	}
	if (currentChoice == 1)
	{
		gsm->quit();
	}
}

bool MenuState::inBounds(int x, int y, int width, int height, int x2, int y2)
{
	// half width
	int hWidth = width / 2;
	int hHeight = height / 2;

	// check whether mouse is inside the text "bounding box"
	if (x2 < x - hWidth || x2 > x + hWidth || y2 < y - hHeight || y2 > y + hHeight)
	{
		return false;
	}

	return true;
}
