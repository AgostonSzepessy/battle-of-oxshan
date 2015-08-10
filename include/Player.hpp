#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Constants.hpp"
#include "AnimatedSprite.hpp"
#include "Frame.hpp"
#include "HealthBar.hpp"
#include "ParticleSystem.hpp"

/**
 * @brief The Player class encapsulates the player. It has functions
 * for updating, drawing, teleporting, and everything else that the
 * player can do.
 */
class Player : public Entity
{
	public:
		/**
		 * @brief Player Creates a new Player object
		 * @param x The x position of the object
		 * @param y The y position of the object
		 * @param filename The path to the player's spritesheet
		 */
		Player(int x, int y, std::string filename);
		~Player();
		/**
		 * @brief update Updates the player's position, his animation
		 * frames, checks if he can shoot, or if he collided with the
		 * bricks.
		 * @param box The bounding box for the bricks.
		 */
		void update(const BoundingBox &box);
		/**
		 * @brief draw Draws the player on the screen.
		 * @param window The window to draw him on
		 */
		void draw(sf::RenderWindow *window);
		/**
		 * @brief hit Called when the player gets hit. It reduces
		 * his health by "damage".
		 * @param damage Amount to reduce player's health by
		 */
		void hit(int damage);
		/**
		 * @brief heal Heals the player for 50 hitpoints.
		 */
		void heal();
		/**
		 * @brief addInvincibilityPotion Adds an invincibility
		 * potion to the player.
		 */
		void addInvincibilityPotion();
		/**
		 * @brief getNumInvincibilityPotions Gets how many invincibility
		 * potions the player can use.
		 * @return Number of invincibility potions player has
		 */
		int getNumInvincibilityPotions();
		/**
		 * @brief setInvincible Makes the player invincible
		 */
		void setInvincible();
		/**
		 * @brief isInvincible Checks if the player is invincible.
		 * @return True if player's invincible
		 */
		bool isInvincible();
		/**
		 * @brief addHealthPotion Adds a health potion to the player
		 */
		void addHealthPotion();
		/**
		 * @brief getNumHealthPotions Gets the number of health potions the
		 * player has remaining.
		 * @return Number of health potions player has left.
		 */
		int getNumHealthPotions();
		/**
		 * @brief getDamage Gets the damage that the player deals
		 * @return How much damage the player deals
		 */
		int getDamage();
		/**
		 * @brief isDead Checks if the player is dead.
		 * @return True if the player's dead.
		 */
		bool isDead();
		bool hasDyingAnimationStarted();
		void setTeleporting(bool b);
		bool getTeleporting() const;
		bool getTeleporting();
		/**
		 * Get the staff x so the fireball can be fired
		 * from the center of the staff.
		 * @return The x position of the player's staff
		 */
		int getStaffX();
		/**
		 * Get the staff y so the fireball can be fired
		 * from the center of the staff.
		 * @return The y position of the player's staff
		 */
		int getStaffY();

		/**
		 * Sets the teleport destination.
		 */
		void teleport(int x, int y);

		/**
		 * Check if the player is moving left.
		 * @return Whether the player is moving left
		 */
		bool getMovedLeft();

		/**
		 * Check if the player is moving right.
		 * @return Whether player is moving right
		 */
		bool getMovedRight();

		/**
		 * Check if the player is moving up.
		 * @return Whether the player is moving up
		 */
		bool getMovedUp();

		/**
		 * Check if the player is moving down.
		 * @return Whether the player is moving down
		 */
		bool getMovedDown();

		/**
		 * Make the player move right.
		 * @param b Set to true if player is moving right, false if not
		 */
		void setMovedRight(bool b);

		/**
		 * Make the player move left.
		 * @param b Set to true if player is moving left, false if not
		 */
		void setMovedLeft(bool b);

		/**
		 * Make the player move up.
		 * @param b Set to true if player is moving up, false if not
		 */
		void setMovedUp(bool b);

		/**
		 * Make the player move down.
		 * @param b Set to true if player is moving down, false if not
		 */
		void setMovedDown(bool b);

	protected:

	private:
		/**
		 * Moves the player to its next position. It also handles collision
		 * detection, animation changes, dying, and teleportation.
		 * @param box The box that is on the battlefield
		 */
		void move(const BoundingBox &box);
		/**
		 * @brief invincibleTimer Checks if the player is still invincible; he
		 * can only be invincible for 3 seconds.
		 * @return True if player is invincible
		 */
		bool invincibleTimer();

		/**
		 * The amount of time the player is invincible for. When the accumulator
		 * is greater than this, the player is vulnerable again.
		 */
		int invTime;
		/**
		 * Used for holding the time from when invincibility was activated.
		 */
		int invPrevTime;
		/**
		 * Holds the current time.
		 */
		int invCurrentTime;
		/**
		 * Holds the total time. Each frame, more time gets
		 * added to it until it is greater or equal to delay.
		 * Then it gets reset.
		 */
		int invAccumulator;

		const int maxSpeed = 5;
		const int acceleration = 1;

		Frame *standing;
		Frame *walking;
		Frame *dying;
		/**
		 * First half of teleport animation. After that, player gets moved to desination
		 */
		Frame *teleportStart;
		/**
		 * Second half of teleport animation that plays after
		 * the player gets moved to the new location.
		 */
		Frame *teleportEnd;

		/**
		 * The health bar of the player. It shows how much
		 * health the player has left.
		 */
		HealthBar *healthBar;
		/**
		 * The maximum health of the player. Health
		 * can't go above this.
		 */
		const int maxHealth = 100;
		/**
		 * The current amount of healt the player has.
		 * It starts equal to maxHealth.
		 */
		int health;
		int damage;
		/**
		 * Teleportation destination x
		 */
		int teleportX;
		/**
		 * Teleportation destination y.
		 */
		int teleportY;

		/**
		 * Keeps track of which animation is currently playing.
		 */
		int currentAnimation;
		const int STANDING = 0;
		const int WALKING = 1;
		const int DYING = 2;
		const int TELEPORT_START = 3;
		const int TELEPORT_END = 4;

		/**
		 * True if player is facing right, and false if he is facing left.
		 * Used for checking whether the setScale() has to be called.
		 */
		bool facingRight;

		/**
		 * Used for playing dying animation. If player is dying, then
		 * don't update him.
		 */
		bool isDying;
		/**
		 * Signals game over.
		 */
		bool dead;
		/**
		 * Used for playing player dying sound.
		 */
		bool dyingAnimationStarted;
		/**
		 * True if player is teleporting and false if he is not. If it is
		 * true, then it blocks input.
		 */
		bool teleporting;

		// moving stuff
		/**
		 * Used to determine whether the player is moving left.
		 */
		bool movedLeft;
		/**
		 * Used to determine whether the player is moving right.
		 */
		bool movedRight;
		/**
		 * Used to determine whether the player is moving up.
		 */
		bool movedUp;
		/**
		 * Used to determine whether the player is moving down.
		 */
		bool movedDown;

		ParticleSystem *particleSystem;

		int numHealthPotions;
		int numInvincibilityPotions;
		bool invincible;
};
