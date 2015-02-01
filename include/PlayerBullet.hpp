#pragma once

#include <memory>

#include "Bullet.hpp"

/**
 * @brief The PlayerBullet class Bullet that the player shoots.
 * If any one of these hits an enemy, the enemy's health will be
 * reduced.
 */
class PlayerBullet : public Bullet
{
	public:
		/**
		 * @brief create Creates a new PlayerBullet in the form of std::unique_ptr<PlayerBullet>
		 * @param x1 The x position of the player
		 * @param y1 The y position of the player
		 * @param x2 The x position of the mouse
		 * @param y2 The y position of the mouse
		 * @param damage The damage that the bullet will deal
		 * @return an std::unique_ptr<PlayerBullet>
		 */
		static std::unique_ptr<PlayerBullet> create(int x1, int y1, int x2, int y2, int damage);
		~PlayerBullet();
		
	protected:
		PlayerBullet(int entityPositionX, int entityPositionY, int mousePositionX, int mousePositionY, int damage, std::string path, int x1, int y1, int xoffset, int yoffset);
		
	private:
		
};
