#pragma once
#include <cmath>
#include <SFML/System.hpp>
#include <random>
#include <chrono>
#include <ctime>

using namespace std::chrono_literals;

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

//struct Time {
//	static float GetDelta() {
//		return (std::chrono::steady_clock::now() - start).count();
//	}
//	static void Update() {
//		start = std::chrono::steady_clock::now();
//	}
//
//private:
//
//	static std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> start;
	//static std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> end;
//	static sf::Clock _clock;
//};
