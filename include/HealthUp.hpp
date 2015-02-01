#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "Powerup.hpp"
#include "Player.hpp"
#include "Frame.hpp"
#include "Constants.hpp"

/**
 * @brief The HealthUp class Encapsulates a health potion. It
 * has functions to get the heal amount, and the effect it has
 * on the player.
 */
class HealthUp : public Powerup
{
	public:
		/**
		 * @brief create Creates an std::unique_ptr<HealthUp>
		 * @param x The x position of the HealthUp
		 * @param y The y position of the HealthUp
		 * @return an std::unique_ptr<HealthUp> pointing to a new HealthUp
		 */
		static std::unique_ptr<HealthUp> create(int x, int y);
		/**
		 * @brief effect The effect that it has on the player is that it
		 * heals him by 50.
		 * @param p The player
		 */
		void effect(Player &p);
		/**
		 * @brief getHealAmount Gets the amount that it heals
		 * @return The amount of health restored
		 */
		static int getHealAmount();
		~HealthUp();
	protected:
	
	private:
		HealthUp(int x, int y);
		
		Frame *frame;
};
