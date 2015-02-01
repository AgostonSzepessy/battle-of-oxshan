#include "EnemyBullet.hpp"

EnemyBullet::EnemyBullet(int entityPositionX, int entityPositionY, int mousePositionX, int mousePositionY, int damage, std::string path, int x1, int y1, int xoffset, int yoffset, int angle)
	: Bullet(entityPositionX, entityPositionY, mousePositionX, mousePositionY, path, x1, y1, xoffset, yoffset)
{
	this->damage = damage;
	if (angle != 0)
		sprite->setRotation(angle);
}

EnemyBullet::~EnemyBullet()
{

}

std::unique_ptr<EnemyBullet> EnemyBullet::create(int x1, int y1, int x2, int y2, int damage, BulletType type)
{
	if (type == BULLET)
	{
		std::unique_ptr<EnemyBullet> b(new EnemyBullet(x1, y1, x2, y2, damage, "res/sprites/projectiles/bullet.png", 0, 0, 11, 11, 0));
		return b;
	}
	else
	{
		// find distance between player and mouse position to figure out how much to rotate the fireball
		int xdist = x2 - x1;
		int ydist = y2 - y1;

		// convert to degrees b/c setRotation uses degrees
		int angle = atan2(ydist, xdist) * 180 / M_PI;

		std::unique_ptr<EnemyBullet> b(new EnemyBullet(x1, y1, x2, y2, damage, "res/sprites/projectiles/lightning-bolt.png", 0, 0, 30, 34, angle));
		return b;
	}
}
