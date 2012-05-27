#include <iostream>
#include <cstddef>
#include "GraphPath.h"

GraphPath::GraphPath(unsigned int node_id) {
	this->nodes.push(node_id);
	this->path = NULL;
}

GraphPath::~GraphPath() {
	if (this->path != NULL) delete this->path;
}
	
void GraphPath::add(unsigned int node_id) {
	this->nodes.push(node_id);
}


unsigned short GraphPath::get_path_length() {
	return this->nodes.size();
}

/*
 * Returns an array describing the path from start to finish.  Clears
 * the path's memory stack.
 * 
 * TODO: Should also compress the path (remove cycles).
 */
unsigned int* GraphPath::get_path() {
	this->path = new unsigned int[this->nodes.size()];
	unsigned int i = 0;
	
	while (!this->nodes.empty()) {
		path[i++] = this->nodes.top();
		std::cout << "  Unwinding path: " << this->nodes.top() << std::endl;
		this->nodes.pop();
	}
	
	return path;
}
