#ifndef GRAPH_H
#define GRAPH_H

#include <string>

class Graph {
	public:
	Graph(std::string filename);
	~Graph();
	
	unsigned int* read_graph();
	void form_graph(unsigned int*);
	
	unsigned int* get_neighbors(unsigned int nid);
	unsigned short get_num_neighbors(unsigned int nid);
	unsigned int num_nodes();
	bool built_successfully();

	private:
	unsigned int** adj_list;
	unsigned short* num_outlinks; // Stores the number of outlinks per node.
								// This array should be the same length as
	unsigned int node_count;
	
	// Passed in as a parameter to the constructor.
	std::string filename;
};

#endif
