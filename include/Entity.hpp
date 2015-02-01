#pragma once

#include <iostream>
#include <complex>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Constants.hpp"
#include "AnimatedSprite.hpp"
#include "HealthBar.hpp"
#include "Brick.hpp"
#include "BoundingBox.hpp"

/**
 * @brief The Entity class Encapsulates an entity. Almost everything
 * that is on the screen is an entity. Entities have the ability to move,
 * deal damage and die.
 */
class Entity
{
	public:
		/**
		 * @brief Entity Creates a new Entity. It also initializes
		 * variables that almost all entities use.
		 */
		Entity();
		virtual ~Entity();
		/**
		 * @brief checkCollision Checks if there's a collision with another
		 * Entity.
		 * @param e The Entity to check collision with
		 * @return True if there's a collision
		 */
		bool checkCollision(const Entity &e);
		/**
		 * @brief checkCollision Checks for a "bounding box collision" between a BoundingBox
		 * and an Entity. Usually used for Bullets
		 * @param b The BoundingBox around the Bricks
		 * @return True if there's an entity inside of the box
		 */
		bool checkCollision(const BoundingBox &b);
		/**
		 * @brief checkBrickCollision Checks if an Entity collides with a BoundingBox.
		 * If they do, it handles it.
		 * @param box The BoundingBox around the Bricks
		 */
		void checkBrickCollision(const BoundingBox &box);		
		/**
		 * @brief checkBounds Checks if the Entity has exited the screen.
		 * If they have, it puts them back.
		 */
		void checkBounds();
		/**
		 * @brief getX Gets the x position of the Entity
		 * @return Entity x position
		 */
		int getX() const;
		/**
		 * @brief getY Gets the y position of the Entity
		 * @return Entity y position
		 */
		int getY() const;
		/**
		 * @brief getWidth Gets the Entity width
		 * @return Entity width
		 */
		int getWidth() const;
		/**
		 * @brief getHeight Gets the height of the entity
		 * @return Entity height
		 */
		int getHeight() const;
		/**
		 * @brief getPosition Gets the position of the Entity
		 * @return a Vector2f that has the position
		 */
		sf::Vector2f getPosition();
		/**
		 * @brief getSprite Gets the sprite of the Entity
		 * @return Entity sprite
		 */
		AnimatedSprite getSprite() const;
		/**
		 * @brief canFire Checks if the Entity can fire. This is to stop
		 * the Entity from having a continous stream of bullets with literally
		 * no break in between each of them.
		 * @return True if they can fire.
		 */
		bool canFire();
		/**
		 * @brief hit If the Entity is hit, then subtract the damage.
		 * @param damage Damage to subtract form Entity health
		 */
		void hit(int damage);
		
	protected:
		/**
		 * Set the position of the enemy to x, and y.
		 * @param x The x position of the entity
		 * @param y The y position of the entity
		 */
		void setPosition(int x, int y);
		
		// positions and vector
		/**
		 * The x position/vector component of the entity.
		 */
		double x;
		/**
		 * The y position/vector component of the entity.
		 */
		double y;
		/**
		 * Stands for 'delta x.' It is how much x is changed
		 * by each frame. It gets added to x.
		 */
		double dx;
		/**
		 * Stands for 'delta y.' It is how much y is changed
		 * by each frame. It gets added to y.
		 */
		double dy;
		
		/**
		 * The x destination of the entity. This gets calculated
		 * every frame, and it's used to see whether the entity
		 * is inside the BoundingBox of the bricks. This prevents
		 * the need to modify x prematurely, and helps avoid other bugs.
		 */
		int xdest;
		/**
		 * The y destination of the entity. This gets calculated
		 * every frame, and it's used to see whether the entity
		 * is inside the BoundingBox of the bricks. This prevents
		 * the need to modify y prematurely, and helps avoid other bugs.
		 */
		int ydest;
		/**
		 * This is the temporary x variable. Instead of using the actual x
		 * variable of the entity in collision detection, this is used.
		 * This also helps avoid bugs by not modifying x, just like xdest.
		 */
		int tempx;
		/**
		 * This is the temporary y variable. Instead of using the actual y 
		 * variable of the entity in collision detection, this is used.
		 * This also helps avoid bugs by not modifying y, just like ydest.
		 */
		int tempy;
		
		/**
		 * How much to slow down the entity by in each frame.
		 */
		double friction = 0.95;
		
		
		/**
		 * The width of the entity.
		 */
		int width;
		/**
		 * The height of the entity.
		 */
		int height;
		
		// variable for textures
		/**
		 * The texture of the entity. It is a spritesheet.
		 */
		sf::Texture *texture;
		/**
		 * The class that takes the texture and draws it. It
		 * also sets the texture's position on the screen, and
		 * gives the collision box of the entity. It takes a Frame
		 * from the spritesheet to know what part of the spritesheet
		 * to draw.
		 */
		AnimatedSprite *sprite;
		
		// variables for shooting
		/** 
		 * Clock to keep track of whether entities can fire bullets.
		 */
		sf::Clock *c;		
		/** 
		 * How much time has passed between shots. If it's greater
		 * than delay, the entity can fire.
		 */
		sf::Time *elapsed;
		/**
		 * The time of the when the previous shot was fired. This is used for
		 * calculating whether *elapsed is greater than delay.
		 */
		sf::Time *last;
		/**
		 * Delay between shots. Measured in milliseconds.
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
		
		// variables for collision detection
		/**
		 * Gives you what side the of the BoundingBox the entity is on.
		 * It is used for collision detection. Without this, the entity 
		 * would get caught on a corner of the BoundingBox.
		 */
		int currentSide;
		/**
		 * Right side of the BoundingBox.
		 */
		int RIGHT_SIDE = 1;
		/**
		 * Left side of the BoundingBox.
		 */
		int LEFT_SIDE = 2;
		/**
		 * Top side of the BoundingBox.
		 */
		int TOP_SIDE;
		/**
		 * Bottom side of the BoundingBox.
		 */
		int BOTTOM_SIDE;
		
	private:
	
	
};
