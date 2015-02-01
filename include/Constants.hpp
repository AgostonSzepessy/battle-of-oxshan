#pragma once

/**
 * @brief HEIGHT The height of the window
 */
const int HEIGHT = 720;
/**
 * @brief WIDTH The width of the window
 */
const int WIDTH = HEIGHT * 4 / 3;

/**
 * The size of bricks that are square.
 */
const int BRICK_SIZE = 64;

/**
 * @brief HEAL_AMOUNT The amount that health potions heal.
 */
const int HEAL_AMOUNT = 50;

// windows doesn't provide pi value
#ifdef _WIN32
#define M_PI 3.14159265358979323846
#endif
