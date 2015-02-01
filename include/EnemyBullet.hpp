#pragma once

#include <memory>
#include <cmath>

#include "Bullet.hpp"

/**
 * @brief The BulletType enum The types of bullets that the Enemy
 * Bullets can be.
 */
enum BulletType
{
	LIGHTNING_BOLT,
	BULLET,
};

/**
 * @brief The EnemyBullet class Encapsulates a bullet. Whenever an object of this
 * class hits the player, the player's health goes down.
 */
class EnemyBullet : public Bullet
{
	public:
		~EnemyBullet();
		/**
		 * @brief create Creates a new std::unique_ptr<EnemyBullet> object.
		 * @param x1 x position of Enemy
		 * @param y1 y position of Enemy
		 * @param x2 x position of player
		 * @param y2 y position of player
		 * @param damage Damage to be dealt to player
		 * @param type Type of bullet: either LIGHTNING_BOLT or BULLET
		 * @return an std::unique_ptr<EnemyBullet> pointing to a new EnemyBullet
		 */
		static std::unique_ptr<EnemyBullet> create(int x1, int y1, int x2, int y2, int damage, BulletType type);
		
	protected:
		EnemyBullet(int entityPositionX, int entityPositionY, int mousePositionX, int mousePositionY, int damage, std::string path, int x1, int y1, int xoffset, int yoffset, int angle);
		
	private:
	
};
