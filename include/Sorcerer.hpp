#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Frame.hpp"
#include "BoundingBox.hpp"

/**
 * @brief The Sorcerer class The Sorcerer is an enemy that can
 * teleport through bricks and shoot lightning bolts at the player.
 */
class Sorcerer : public Enemy
{
	public:
		/**
		 * @brief create Creates a new Sorcerer at position (x,y) and returns
		 * an std::unique_ptr<Sorcerer>
		 * @param x The x position of the Sorcerer
		 * @param y The y position of the Sorcerer
		 * @return std::unique_ptr<Sorcerer>
		 */
		static std::unique_ptr<Sorcerer> create(int x, int y);
		/**
		 * @brief update Updates the Sorcerer's position, checks if
		 * he needs to teleport, if he needs to shoot, and updates his
		 * animation.
		 * @param e The entity to move towards; the Player
		 * @param box The bounding box around the bricks
		 */
		void update(const Entity &e, const BoundingBox &box);
		/**
		 * @brief draw Draws the sorcerer
		 * @param window The window to draw him on
		 */
		void draw(sf::RenderWindow *window);
		/**
		 * @brief isReloading Checks if the sorcerer is reloading. Since
		 * he doesn't use a gun, he never needs to reload.
		 * @return false
		 */
		bool isReloading()
		{
			return false;
		}
		~Sorcerer();
		
	protected:
		
	private:
		Sorcerer(int x, int y);
		void teleport(int x, int y);
		void move(const BoundingBox &b);
		
		const std::string filename = "res/sprites/enemy/sorcerer-spritesheet.png";
		
		Frame *teleportStart;
		Frame *teleportEnd;
		Frame *walking;
		
		int teleportX;
		int teleportY;
		bool teleporting;
		
		const int TELEPORT_START = 3;
		const int TELEPORT_END = 4;
		
		const int maxSpeed = 5;
		const int acceleration = 1;
};
