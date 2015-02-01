#include "PlayerBullet.hpp"

PlayerBullet::PlayerBullet(int entityPositionX, int entityPositionY, int mousePositionX, int mousePositionY, int damage, std::string path, int x1, int y1, int xoffset, int yoffset)
	: Bullet(entityPositionX, entityPositionY, mousePositionX, mousePositionY, path, x1, y1, xoffset, yoffset)
{
	this->damage = damage;

	// find distance between player and mouse position to figure out how much to rotate the fireball
	int xdist = mousePositionX - entityPositionX;
	int ydist = mousePositionY - entityPositionY;

	// convert to degrees b/c setRotation uses degrees
	int angle = atan2(ydist, xdist) * 180 / M_PI;
	sprite->setRotation(angle);

	speed = 10;
}

PlayerBullet::~PlayerBullet()
{

}

std::unique_ptr<PlayerBullet> PlayerBullet::create(int x1, int y1, int x2, int y2, int damage)
{
	std::unique_ptr<PlayerBullet> b(new PlayerBullet(x1, y1, x2, y2, damage, "res/sprites/projectiles/fireball.png", 0, 0, 41, 23));

	return b;
}

