#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "stdio.h"

using namespace std;

struct Edge final : public sf::Drawable {
	explicit Edge(Node* local, Node* remote, sf::Color color = sf::Color::Green) {
		this->local = local;
		this->remote = remote;
		this->color = color;
	}

	auto setColor(const sf::Color color) -> void { this->color = color; }
	auto setLocal(Node* local) -> void { this->local = local; }
	auto setRemote(Node* remote) -> void { this->remote = remote; }

	[[nodiscard]] auto getLocal() const -> Node* { return local; }
	[[nodiscard]] auto getRemote() const -> Node* { return remote; }

private:
	Node* local;
	Node* remote;
	sf::Color color;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

		sf::Vertex const line[2]{
			sf::Vertex{local->getPosition(), sf::Color::White},
			sf::Vertex{remote->getPosition(), sf::Color::White}
		};
		target.draw(line, 2, sf::PrimitiveType::Lines, states);
	}

};
