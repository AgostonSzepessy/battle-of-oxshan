#pragma once

#include <iostream>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Enemy.hpp"
#include "EnemyBullet.hpp"
#include "Frame.hpp"
#include "BoundingBox.hpp"

/**
 * @brief The BlueThing class The BlueThing is an enemy that
 * shoots bullets in a circle around itself, while moving towards
 * the player.
 */
class BlueThing : public Enemy
{
	public:
		/**
		 * @brief create Creates an std::unique_ptr<BlueThing> and sets its position.
		 * @param x X position
		 * @param y Y position
		 * @return An std::unique_ptr<BlueThing>
		 */
		static std::unique_ptr<BlueThing> create(int x, int y);
		~BlueThing();
		/**
		 * @brief update Updates the BlueThing by setting the appropriate animation, checking
		 * for a collision with the bricks, and by moving it towards the player.
		 * @param e The Entity that it's moving towards
		 * @param box The bounding box for bricks
		 */
		void update(const Entity &e, const BoundingBox &box);
		/**
		 * @brief draw Draws the BlueThing on the screen.
		 * @param window The window to draw it on.
		 */
		void draw(sf::RenderWindow *window);
		/**
		 * @brief isReloading Checks if the BlueThing is reloading. If it's reloading, then
		 * the BlueThing takes a break from shooting, plays the reload sound and reloads.
		 * @return True if it is reloading.
		 */
		bool isReloading();
		
	protected:
		
	private:
		BlueThing(int x, int y);
		
		bool reloading;
		bool startReload;
		int reloadAccumulator;		
};
