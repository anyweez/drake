#include <iostream>

#include "drake.h"
#include "Graph.h"

void load_test() {
	Graph g(GRAPH_FILE_NAME);
	
	// Print each node line.
	for (unsigned int nid = 0; nid < g.num_nodes(); nid++) {
		std::cout << nid << '\t';
		std::cout << g.get_num_neighbors(nid) << '\t';
		
		unsigned int* neighbors = g.get_neighbors(nid);
		for (unsigned int neighbor = 0; neighbor < g.get_num_neighbors(nid); neighbor++) {
			std::cout << neighbors[neighbor] << '\t';
		}
		std::cout << std::endl;
	}
}
