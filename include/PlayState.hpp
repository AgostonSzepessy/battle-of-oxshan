#pragma once

#include <iostream>
#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>
#include <typeinfo>
#include <cstdlib>
#include <ctime>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameStateManager.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "BlueThing.hpp"
#include "Player.hpp"
#include "Constants.hpp"
#include "PlayerBullet.hpp"
#include "EnemyBullet.hpp"
#include "Brick.hpp"
#include "BoundingBox.hpp"
#include "HealthUp.hpp"
#include "InvincibilityUp.hpp"
#include "Background.hpp"
#include "Sorcerer.hpp"
#include "GameOverState.hpp"

/**
 * @brief The PlayState class This is where most of the game
 * takes place. The player fights the enemies here.
 */
class PlayState : public GameState
{
	public:
		~PlayState();
		/**
		 * @brief Updates everything that has to be updated.
		 */
		void update();
		/**
		 * @brief draw Draws everything that needs to be drawn
		 */
		void draw();
		/**
		 * @brief Handles all the input that the user gives.
		 */
		void handleInput();
		/**
		 * @brief build Creates the PlayState
		 * @param window Window to draw everything on
		 * @param gsm GameStateManager that manages state switching
		 * @return std::unique_ptr<PlayState>
		 */
		static std::unique_ptr<PlayState> build(sf::RenderWindow *window, GameStateManager *gsm);
		
	protected:
		
	private:
		/**
		 * This function sets up the PlayState and creates the first wave of 
		 * enemies, and bricks.
		 */
		PlayState(sf::RenderWindow *window, GameStateManager *gsm);
		/**
		 * Sets up the PlayState by initializing variables and setting the
		 * text variables.
		 */
		void create();
		/**
		 * Creates the bricks at a random position.
		 */
		void makeBricks();
		/**
		 * Adds a std::unique_ptr bullet to the bullets vector.
		 */
		void addBullet(std::unique_ptr<Bullet> b);
		/**
		 * Creates the next wave of enemies.
		 */
		void createWave();
		/**
		 * Sets the continue text.
		 */
		void setContinueText();
		/**
		 * This is a timer and it returns true 1 second after the new wave has started.
		 * If it returns true, the text is not displayed.
		 */
		bool deleteText();
		/**
		 * Returns a unique_ptr for sf::SoundBuffer so the soundBuffers vector can be
		 * initialized in a loop.
		 */
		std::unique_ptr<sf::SoundBuffer> createSoundBuffer();
		/**
		 * Returns a unique_ptr for sf::Sound so the sounds vector can be initialized
		 * in a loop.
		 */
		std::unique_ptr<sf::Sound> createSound();
		
		/**
		 * The pointer that points to the player.
		 */
		Player *player;
		/**
		 * The bounding box for the bricks. This is used for collision 
		 * detection with the bricks.
		 */
		BoundingBox *boundingBox;
		
		/**
		 * This lists all possible sounds that can be played. The elements listed
		 * here are used as indices to an array.
		 */
		enum Sounds
		{
			PLAYER_FIRING = 0,
			PLAYER_HIT,
			PLAYER_DYING,
			FIREBALL_EXPLOSION,
			POWERUP,
			BLUETHING_FIRING,
			BLUETHING_RELOAD,
			BLUETHING_DYING,
			SORCERER_FIRING,
			SORCERER_DYING,
			ENEMY_HIT,
		};
		
		/**
		 * Stores the enemies that are created.
		 */
		std::vector<std::unique_ptr<Enemy>> enemies;
		/**
		 * Stores the bullets that are created.
		 */
		std::vector<std::unique_ptr<Bullet>> bullets;
		/**
		 * Stores the bricks that are created.
		 */
		std::vector<std::shared_ptr<Brick>> bricks;
		/**
		 * Stores the power ups taht are created.
		 */
		std::vector<std::unique_ptr<Powerup>> powerups;
		/**
		 * Stores the sounds that are played.
		 */
		std::vector<std::unique_ptr<sf::Sound>> sounds;
		/**
		 * This is used for playing the sounds.
		 */
		std::vector<std::unique_ptr<sf::SoundBuffer>> soundBuffers;
		/**
		 * This stores the background.
		 */
		std::unique_ptr<Background> background;
		
		/**
		 * This is the health potions that the player has collected. This
		 * is in a separate vector so they are accessible easily. Otherwise,
		 * the powerups vector would have to be searched for a HealthUp.
		 */
		std::vector<std::unique_ptr<HealthUp>> healthPotions;
		
		/**
		 * The wave that the player is on.
		 */
		int waveNumber; 
		/** 
		 * Clock to keep track of whether the waveText can be removed.
		 */
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
		
		/**
		 * The text that appears at the start of each wave
		 * and tells the player what wave he is at. It appears
		 * for 1 second.
		 */
		sf::Text *waveText;
		/**
		 * The font that the waveText uses.
		 */
		sf::Font *font;
		/**
		 * The size of the waveText.
		 */
		const int textSize = 20;
		/**
		 * The color of the waveText.
		 */
		const sf::Color textColor = sf::Color::Black;
		/**
		 * Checks whether player has pushed Tab.
		 */
		bool continueToNextWave;
		
		/**
		 * Checks whether text has been set when the
		 * player is between waves.
		 */
		bool hasSetText;
		/**
		 * This holds the value for whether there is a wave
		 * active, or not. It is used when the player presses
		 * Tab, because if the player presses Tab in the middle of
		 * a wave, then continueToNextWave will be true.
		 */
		bool isWaveActive;
		/**
		 * Restarts the timer for the wave text.
		 */
		bool setTimer;
		
		/**
		 * Displays how many health potions the player has collected.
		 */
		sf::Text *healthPotionsCollected;
		/**
		 * Displays how many health potions the player has collected.
		 */
		sf::Text *invincibilityPotionsCollected;
};
