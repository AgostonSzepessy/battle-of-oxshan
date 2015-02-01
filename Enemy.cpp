#include "Enemy.hpp"

Enemy::Enemy()
{
	isDying = dead = false;
	healthBar = new HealthBar(0, 0);
	standing = new Frame;
	dying = new Frame;
	numTimesFired = 0;
}

Enemy::~Enemy()
{
	delete healthBar;
	delete standing;
	delete dying;
}

int Enemy::getHealth()
{
	return health;
}

void Enemy::moveTowardsPlayer(const Entity &e)
{
	// it has collided with the player, so no need to check for other collisions
	if (checkCollision(e))
	{
		return;
	}

	// slow him down
	dx *= friction;
	dy *= friction;

	// get vector
	int distanceX = e.getX() - x;
	int distanceY = e.getY() - y;

	int speed = 3;

	// get vector magnitude
	int distance = sqrt(distanceX * distanceX + distanceY * distanceY);

	// normalize magnitude and multiply by speed so there's a vector pointing towards the entity
	dx = speed * static_cast<double>(distanceX) / distance;
	dy = speed * static_cast<double>(distanceY) / distance;

}

int Enemy::getDamage()
{
	return damage;
}

void Enemy::hit(int damage)
{
	health -= damage;
	if (health <= 0)
	{
		health = 0;
		isDying = true;
	}
	healthBar->setHealth(health);
}

bool Enemy::isDead()
{
	return dead;
}
