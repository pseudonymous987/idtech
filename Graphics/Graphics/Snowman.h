#pragma once
#include <SFML/Graphics.hpp>

class Snowman final : public sf::Drawable {

	sf::CircleShape* bottom;
	sf::CircleShape* middle;
	sf::CircleShape* top;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(*bottom);
		target.draw(*middle);
		target.draw(*top);
	}

public:
	explicit Snowman(float width, float x, float y, sf::Color color = sf::Color::Magenta) {
		float radius = width / 2.0;
		bottom = new sf::CircleShape(radius);
		bottom->setPosition({ x, y });
		bottom->setFillColor(sf::Color::White);

		middle = new sf::CircleShape(radius * 0.8);
		middle->setPosition({ x + (0.2f * radius), y - (1.2f * radius) });
		middle->setFillColor(sf::Color::White);

		top = new sf::CircleShape(radius * 0.6);
		top->setPosition({ x + (0.4f * radius), y - (2 * radius) });
		top->setFillColor(sf::Color::White);
	}

};
