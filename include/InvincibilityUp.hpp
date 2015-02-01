#pragma once

#include <memory>

#include "Powerup.hpp"
#include "Player.hpp"
#include "Frame.hpp"

/**
 * @brief The InvincibilityUp class Encapsulates an
 * invincibility potion. This class gets its positon
 * set at creation and it has an invincibility effect.
 */
class InvincibilityUp : public Powerup
{
	public:
		/**
		 * @brief create Creates an std::unique_ptr<InvincibilityUp>
		 * @param x The x position of the InvincibilityUp
		 * @param y The y position of the InvincibilityUp
		 * @return an std::unique_ptr<InvincibilityUp> pointing to a new InvincibilityUp
		 */
		static std::unique_ptr<InvincibilityUp> create(int x, int y);
		/**
		 * @brief effect The effect that it has on the player; it makes him
		 * invincible.
		 * @param p The player
		 */
		void effect(Player &p);
		~InvincibilityUp();
	private:
		InvincibilityUp(int x, int y);
		Frame *frame;
	protected:
};
