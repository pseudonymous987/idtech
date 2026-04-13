#pragma once
#include <cfloat>
#include <map>
#include "Edge.h"

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
		std::cout << value << std::endl;
	}*/

	void createRandomGraph(int numNodes, int maxWidth, int maxHeight) {

		srand(time(0));

		for (int i = 0; i < numNodes; i++) {
			int x = rand() % maxWidth;
			int y = rand() % maxHeight;
			Node* subject = new Node(i, x, y);
			nodes.push_back(subject);
		}

		for (int i = 0; i < numNodes; i++) {
			if (numNodes <= 1) {
				break;
			}
			int temperature = randInt(numNodes - 1);
			int humidity;
			for (humidity = randInt(numNodes - 1); humidity != temperature; humidity = randInt(numNodes - 1));

			Node* local = nodes[temperature];
			Node* remote = nodes[humidity];

			Edge* subject = new Edge(local, remote);
			edges.push_back(subject);
		}

		//std::cout << edges.size() << std::endl;
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
			std::cout << edge->getLocal()->getKey() + " " + edge->getRemote()->getKey() << std::endl;
			target.draw(*edge, states);
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
};
