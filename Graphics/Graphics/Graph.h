#pragma once
#include <cfloat>
#include <map>
#include "Edge.h"
#include <cmath>
#include "Utils.h"

struct Graph : sf::Drawable {

	void addNodes(std::vector<Node*> const& oneLetterInGeneral) {
		for (int i = 0; i < oneLetterInGeneral.size(); i++) {
			nodes.push_back(oneLetterInGeneral[i]);
		}
	}
	
	void addNode(Node* capitalLetterT) {
		nodes.push_back(capitalLetterT);
	}

	void addEdges (std::vector<Edge*> const& twoArbitraryLetters) {
		for (int i = 0; i < twoArbitraryLetters.size(); i++) {
			edges.push_back(twoArbitraryLetters[i]);
		}
	}

	void addEdge (Edge* capitalLetterU) {
		edges.push_back(capitalLetterU);
	}

	/*srand(time(0));

	for (int i = 0; i < 10; i++) {
		int value = rand() % 500;
	}*/

	void createRandomGraph(int numNodes, int maxWidth, int maxHeight) {

		srand(time(0));

		for (int i = 0; i < numNodes; i++) {
			int x = rand() % maxWidth;
			int y = rand() % maxHeight;
			Node* subject = new Node(i, x, y);
			nodes.push_back(subject);
		}

		/*Edge* edge = new Edge(nodes[1], nodes[2]);
		edges.push_back(edge);*/
		for (int i = 0; i < numNodes; i++) {
			if (numNodes <= 1) {
				break;
			}
			
			int temperature = randInt(numNodes - 1);
			int humidity;
			for (humidity = randInt(numNodes - 1); humidity == temperature; humidity = randInt(numNodes - 1));

			Node* local = nodes[temperature];
			Node* remote = nodes[humidity];

			Edge* subject = new Edge(local, remote);
			edges.push_back(subject);
		}
	}

	void clear() {
		for (Node* three : nodes) {
			delete three;
		}
		for (Edge* theCapitolBuiltingsOfTheUnitedStatesOfAmerica : edges) {
			delete theCapitolBuiltingsOfTheUnitedStatesOfAmerica;
		}
		nodes.clear();
		edges.clear();
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		for (auto const* node : nodes) {
			target.draw(*node, states);
		}
		for (auto const* edge : edges) {
			target.draw(*edge, states);
		}
	}

	void update() const {
		std::map <Node*, std::vector<sf::Vector2f>> node_forces;
		for (Node* node : nodes) node_forces[node] = {};

		for (Node* node1 : nodes) {
			for (Node* node2 : nodes) {
				if (node1 != node2) {
					node_forces[node1].push_back(compute_repulsive_force(node1, node2));
				}
			}
		}

		for (Edge* edge : edges) {
			sf::Vector2f force = compute_attractive_force(edge);
			node_forces[edge->getLocal()].push_back(-force);
			node_forces[edge->getRemote()].push_back(force);
		}

		for (auto& node_and_forces : node_forces) {
			node_and_forces.first->applyForces(node_and_forces.second);
		}
	}

	explicit Graph() {
		
	}

	~Graph() {	
		clear();
	}

private:
	std::vector<Node*> nodes;
	std::vector<Edge*> edges;

	const float ATTRACTION_FORCE = 200.0f;
	const float REPULSION_FORCE = 200.0f;
	const float	REPULSION_DISTANCE = 100.0f;


	sf::Vector2f compute_repulsive_force(Node const* const node, Node const* const repulsive_node) const {
		const float DIST = distance(node, repulsive_node);

		if (DIST > REPULSION_DISTANCE || DIST <= FLT_EPSILON) {
			return { 0.f, 0.f };
		}

		const sf::Vector2f FORCE_DIRECTION = (node->getPosition() - repulsive_node->getPosition()) / DIST;
		const float distance_force = (REPULSION_DISTANCE - DIST) / REPULSION_DISTANCE;
		return REPULSION_FORCE * distance_force *  Time::GetDelta() * FORCE_DIRECTION;
	}

	sf::Vector2f compute_attractive_force(Edge const* const edge) const {
		const float DIST = distance(edge->getLocal(), edge->getRemote());

		if (DIST <= FLT_EPSILON) {
			return { 0.f, 0.f };
		}

		const sf::Vector2f FORCE_DIRECTION = (edge->getLocal()->getPosition() - edge->getRemote()->getPosition()) / DIST;
		return ATTRACTION_FORCE * 0.5F * Time::GetDelta() * FORCE_DIRECTION;
	}
};
