#include <iostream>
#include <ctime>
#include <cstdlib>
#include "GraphDiver.h"
#include "GraphPath.h"

GraphDiver::GraphDiver() {
	
}

GraphDiver::~GraphDiver() {
	
}
		
GraphPath* GraphDiver::search(Graph* graph, GraphQuery& query) {
	srand( time(NULL) );
	return this->_search(graph, query, query.get_start(), 0);
}
		
GraphPath* GraphDiver::_search(Graph* graph, GraphQuery& query, unsigned int loc, unsigned short depth) {
	// Base case #1: found goal.  Instant win.
	if (loc == query.get_end()) {
		std::cout << "Found end!" << std::endl;
		return new GraphPath(loc);
	}
	// Base case #2: reached maximum depth.  Instant fail.
	else if (depth >= query.get_depth_limit()) {
		return NULL;
	}
	
	unsigned int* neighbors = graph->get_neighbors(loc);
	unsigned short num_neighbors = graph->get_num_neighbors(loc);
	GraphPath* path = NULL;
	
	// Search all neighbors.  Stop if we find one that works.
	for (unsigned short neighbor = 0; neighbor < num_neighbors; ++neighbor) {
		path = this->_search(graph, query, neighbors[neighbor], depth + 1);
		if (path != NULL) break;
	}

	// Tried all neighbors and no luck.  Return.
	if (path == NULL) return NULL;
	// Found something.  Append yourself to the path on the way back up the
	// call stack.
	else {
		path->add(loc);
		return path;
	}
}
