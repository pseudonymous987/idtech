#pragma once
#include <iostream>
#include <map>
#include <list>
#include "Node.h"
#include "Edge.h"


class DFS {
public:
	DFS(std::map<Node*, std::list<Node*>> adjList) {
		this->adjList = adjList;
	}

	vector<Node*> traverse(Node* root) {
		std::vector<Node*> visited;
		std::vector<Node*> res;
		traverseRec(visited, res, root);
		std::cout << "Any static message, and size: " << res.size() << std::endl;

		for (int i = 0; i < res.size(); i++) {
			std::cout << res[i]->getKey() << std::endl;
		}

		return res;
	}

	bool search(Node* first, Node* second) {
		//takes in two nodes, T if you can reach them both, F if you cant
	}


private:
	int delay;
	std::map<Node*, std::list<Node*>> adjList;

	void traverseRec(std::vector<Node*>& visited, std::vector<Node*> res, Node* root) {
		bool visit = (std::find(visited.begin(), visited.end(), root) != visited.end());
		if (!visit) {
			visited.push_back(root);
		}

		res.push_back(root);

		for (auto i : adjList[root]) {
			if (std::find(visited.begin(), visited.end(), i) == visited.end()) {
				traverseRec(visited, res, i);
			}
		}


	}
};
