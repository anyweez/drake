#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include "Graph.h"

Graph::Graph(std::string filename) {
	srand( time(NULL) );

	this->filename = filename;
	
	this->node_count = 0;
	this->num_outlinks = NULL;
	this->adj_list = NULL;
	
	this->form_graph(this->read_graph());
}

// TODO: This needs to be debugged once real data is there.
Graph::~Graph() {
	if (this->built_successfully()) {
		delete this->num_outlinks;	
	
		for (unsigned int i = 0; i < this->num_nodes(); ++i) {
			delete adj_list[i];
		}
		delete adj_list;
	}
}

/**
 * Reads in the Wikipedia graph from wikimap.bin.  Returns the raw data,
 * which should then be passed to form_graph().
 */
unsigned int* Graph::read_graph() {
	std::ifstream infile(this->filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	if (infile.is_open()) {
		std::ifstream::pos_type file_size = infile.tellg();
		infile.seekg(0, std::ios::beg);

		unsigned int* raw_graph = new unsigned int[file_size / sizeof(unsigned int)];
		infile.read((char *)raw_graph, file_size);
		
		std::cout << "File is " << file_size << " bytes long." << std::endl;
		
		// Clean up.
		infile.close();
		return raw_graph;
	}
	else {
		std::cerr << "Could not open wikimap.bin.  You need to build the graph first." << std::endl;
		this->node_count = 0;
		return NULL;
	}	
}

/**
 * This method interprets the raw data read from the binary file.  The
 * file contains the full Wikipedia graph (directed, unweighted) and is
 * in the following format:
 * 		node_id		num_outlinks		out_id1		out_id2		...
 * The first unsigned int is the number of nodes in the dataset.
 * All data is encoded as unsigned integers.  There is no delimiting 
 * character between each record since the length of each record can be 
 * determined by the num_outlinks field.
 */
void Graph::form_graph(unsigned int* raw_data) {
	// There was a problem opening the file...let's bail.
	if (raw_data == NULL) {
		return;
	}
	std::cout << "Interpreting node data..." << std::endl;
	unsigned int* ptr = raw_data;
	unsigned int file_nodes = *ptr;
	ptr++;
	
	// This is a one-dimensional array that holds the number of outlinks
	// for each node, indexable by node ID.
	this->num_outlinks = new unsigned short[file_nodes];
    // Initialize everything to 0 so that values that weren't processed (if any)
	// won't be filled with garbage.
	for (unsigned int i = 0; i < file_nodes; i++) {
		this->num_outlinks[i] = 0;
	}

	// This loop iterates once per node.  After each iteration the target node
	// will be fully initialized.
	
//		this->adj_list[current_id] = new unsigned short[this->num_outlinks[current_id]];
	this->adj_list = new unsigned int*[file_nodes];
	std::cout << "Number of nodes: " << file_nodes << std::endl;

	while (this->num_nodes() < file_nodes) {
		unsigned int current_id = *ptr++;
		this->num_outlinks[current_id] = *ptr++;
	
		this->adj_list[current_id] = new unsigned int[this->num_outlinks[current_id]];
		
		for (unsigned int olc = 0; olc < this->num_outlinks[current_id]; olc++) {
			this->adj_list[current_id][olc] = *ptr++;
		}
		
		if (this->num_nodes() % 10000 == 0) {
			std::cout << "Reading nodes : [ " << this->num_nodes() << " / " << file_nodes << " ]\r";
		}

		// Increment the number of nodes.
		this->node_count++;
	}
	std::cout << "Reading nodes : [ " << this->num_nodes() << " / " << file_nodes << " ]\r";
	
	std::cout << std::endl;
	// Delete the raw form.
	delete raw_data;
}

unsigned int Graph::num_nodes() {
	return this->node_count;
}

unsigned int* Graph::get_neighbors(unsigned int nid) {
	// Scramble the neighbors each time they're requested.
	// TODO: This may threaten thread safety.  Investigate.
	for (unsigned int i = 0; i < this->num_outlinks[nid]; ++i) {
		unsigned short from = rand() % this->num_outlinks[nid];
		unsigned short to   = rand() % this->num_outlinks[nid];
	
		unsigned int temp = this->adj_list[nid][from];
		this->adj_list[nid][from] = this->adj_list[nid][to];
		this->adj_list[nid][to] = temp;
	}	
	return this->adj_list[nid];
}

unsigned short Graph::get_num_neighbors(unsigned int nid) {
	return this->num_outlinks[nid];
}

bool Graph::built_successfully() {
	return (this->num_nodes() != 0);
}
