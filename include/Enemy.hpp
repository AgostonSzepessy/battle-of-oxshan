#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "BoundingBox.hpp"

/**
 * @brief The Enemy class Encapsulates an enemy. It has functions that need
 * to be implemented by all enemies. It also has functions that are used to draw
 * it, get the position, and damage, and functions that are used for hitting and
 * killing it.
 */
class Enemy : public Entity
{
	public:
		/**
		 * @brief Enemy Creates a new Enemy.
		 */
		Enemy();
		virtual ~Enemy();
		/**
		 * @brief update Function that needs to be implemented.
		 * @param e Entity to move towards, or fire at
		 * @param box Bounding box around bricks to check collision with it.
		 */
		virtual void update(const Entity &e, const BoundingBox &box) = 0;
		/**
		 * @brief draw Draws the Enemy on the window
		 * @param window Window to draw it on
		 */
		virtual void draw(sf::RenderWindow *window) = 0;
		/**
		 * @brief isReloading Checks if the Enemy is reloading. Not all enemies
		 * need to reload, so some will just return true
		 * @return True if it's reloading
		 */
		virtual bool isReloading() = 0;
		/**
		 * @brief getHealth Gets the health of the Enemy
		 * @return Enemy's health
		 */
		int getHealth();
		/**
		 * @brief getDamage Gets the damage that the enemy deals
		 * @return Damage that enemy deals
		 */
		int getDamage();
		/**
		 * @brief hit Called when the Enemy is hit. It reduces their health.
		 * @param damage Amount to reduce health by
		 */
		void hit(int damage);
		/**
		 * @brief isDead Checks if the enemy is dead.
		 * @return True if enemy is dead
		 */
		bool isDead();
		/**
		 * @brief addToNumTimesFired Adds to the number of times the Enemy fired.
		 * This is used for Enemies that need to reload
		 */
		void addToNumTimesFired()
		{
			numTimesFired++;
		}
		
	protected:
		int maxHealth = 100;
		int health;
		int damage;
		int speed;
		HealthBar *healthBar;
		int prevX;
		int prevY;
		
		bool facingRight;
		bool isDying;
		bool dead;
		Frame *standing;
		Frame *dying;
		
		/**
		 * Keeps track of which animation is playing.
		 */
		int currentAnimation;
		const int STANDING = 0;
		const int WALKING = 1;
		const int DYING = 2;
		
		void moveTowardsPlayer(const Entity &e);
		
		int numTimesFired;
	
	private:
	
};
