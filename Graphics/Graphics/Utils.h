#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

static float eucDistF(sf::Vector2f const& a, sf::Vector2f const& b) {
	sf::Vector2f const delta = a - b;
	return sqrtf(delta.x * delta.x + delta.y * delta.y);
}

static int randInt(int max) {
	srand(time(0));
	return rand() % max;
}
