#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <random>

static float eucDistF(sf::Vector2f const& a, sf::Vector2f const& b) {
	sf::Vector2f const delta = a - b;
	return sqrtf(delta.x * delta.x + delta.y * delta.y);
}

static int randInt(int max) {
	/*srand(time(0));
	return rand() % max;*/

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, max);
	return dist(gen);
}

struct Time {
	static float GetDelta() {
		return _clock.getElapsedTime().asSeconds();
	}
	static void Update() {
		_clock.restart();
	}

private:
	static sf::Clock _clock;
};
