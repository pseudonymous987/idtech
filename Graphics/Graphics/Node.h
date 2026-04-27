#pragma once
#include <SFML/Graphics.hpp>
#include "Utils.h"

struct Node final : public sf::Drawable {
explicit Node(int key, float x = 50, float y = 50, float radius = 12, sf::Color color = sf::Color::White) {
	this->key = key;
	shape = new sf::CircleShape(radius);
	shape -> setPosition({ x, y });
	shape -> setFillColor(color);
}

explicit Node(int key, sf::Vector2f position, float radius = 12, sf::Color color = sf::Color::White) {
	this->key = key;
	shape = new sf::CircleShape(radius);
	shape->setPosition(position);
	shape->setFillColor(color);
}

auto setColor(const sf::Color color) const -> void { shape->setFillColor(color); }
auto setPosition(const sf::Vector2f position) const -> void { shape->setPosition({ position }); }
auto setPosition(const float x, const float y) const -> void { shape->setPosition({ x, y }); }

[[nodiscard]] auto getPosition() const -> sf::Vector2f { return shape->getPosition(); }
[[nodiscard]] auto getColor() const -> sf::Color { return shape->getFillColor(); }

auto changeX(const float x) const -> void {
	change(x, 0);
}

auto changeY(const float y) const -> void {
	change(0, y);
}

auto change(const float x, const float y) const -> void {
	this->shape->move(sf::Vector2f({ x, y }));
}

[[nodiscard]] auto getKey() const -> int { return key; }

auto applyVelocity(const sf::Vector2f velocity) const -> void {
	shape->move(velocity);
}

auto applyForces(std::vector<sf::Vector2f>& forces) const -> void {
	if (forces.empty()) {
		return;
	}

	sf::Vector2f velocity{ 0.0f, 0.0f };

	for (auto const& force : forces) {
		velocity += force;
	}

	const float dist = eucDistF({ 0.0f, 0.0f }, velocity);
	applyVelocity(dist > MAX_VELOCITY_MAGNITUDE ? MAX_VELOCITY_MAGNITUDE * (velocity / dist) : velocity);
}

private:
	int key;
	sf::CircleShape* shape;
	const float MAX_VELOCITY_MAGNITUDE = 300.0f;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(*shape);
	}
};

inline float distance(sf::Vector2f const& a, sf::Vector2f const& b) {
	const sf::Vector2f delta = a - b;
	return sqrtf(delta.x * delta.x + delta.y * delta.y);
}

inline float distance(Node const* const node, sf::Vector2f const& b) {
	const sf::Vector2f delta = node->getPosition() - b;
	return sqrtf(delta.x * delta.x + delta.y * delta.y);
}

inline float distance(Node const* const a, Node const* const b) {
	return distance(a->getPosition(), b->getPosition());
}
