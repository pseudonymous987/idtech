#pragma once
#include <map>
#include <list>
#include "Node.h"
#include "Edge.h"


class DFS {
	DFS(std::map<Node*, std::list<Node*>> adjList) {
		this->adjList = adjList;
	}

	void traverse(Node* root) {
		//prints out path to all nodes
	}

	bool search(Node* first, Node* second) {
		//takes in two nodes, T if you can reach them both, F if you cant
	}


private:
	int delay;
	std::map<Node*, std::list<Node*>> adjList;
};
