#include <iostream>
#include <cstddef>
#include <list>
#include "GraphPath.h"

GraphPath::GraphPath(unsigned int node_id) {
	this->nodes.push_back(node_id);
	this->path = NULL;
	
	this->compressed = false;
}

GraphPath::~GraphPath() {
	if (this->path != NULL) delete [] this->path;
}
	
void GraphPath::add(unsigned int node_id) {
	this->nodes.push_back(node_id);
}


unsigned short GraphPath::get_path_length() {
	// Check to see if the path has been compressed yet.  If not,
	// compress it now to ensure that the correct values are returned.
	if (!this->compressed) this->compress_path();
	
	return this->nodes.size();
}

// Reduces the node list to the shortest form that removes cycles but
// doesn't alter the primary path.
void GraphPath::compress_path() {
	std::list<unsigned int>::iterator src = this->nodes.begin();
	
	// Start at the first element and look for duplicates.
	while (src != this->nodes.end()) {
		// First comparison should be against the last element and work
		// towards the src element.  This will maximize the size of the
		// slice that's removed when a particular value appears more
		// than twice by hitting the first and last appearances before
		// any subcomponent is hit.
		std::list<unsigned int>::iterator dest = --this->nodes.end();		

		while (dest != src) {
			// Remove the elements from the linked list when the value
			// of both nodes matches.
			if (*src == *dest) {
				src = this->nodes.erase(src, dest);
				break;
			}
			dest--;
		}
		src++;
	}
	
	// Flip the flag so that we don't do this again.
	this->compressed = true;
}

/*
 * Returns an array describing the path from start to finish.  Clears
 * the path's memory stack.
 */
unsigned int* GraphPath::get_path() {	
	// Check to see if the path has been compressed yet.  If not, do it
	// now so that the correct path is returned.
	if (!this->compressed)	this->compress_path();

	this->path = new unsigned int[this->nodes.size()];
	std::list<unsigned int>::iterator iter = this->nodes.begin();

	// Add the nodes in reverse order (to simulate popping them off of
	// a stack).
	unsigned int i = this->nodes.size() - 1;	
	while (iter != this->nodes.end()) {
		path[i--] = *iter++;
	}
	
	return this->path;
}
