#ifndef GRAPHPATH_H
#define GRAPHPATH_H

#include <stack>

class GraphPath {
	public:
	GraphPath(unsigned int node_id);
	~GraphPath();
	
	void add(unsigned int node_id);
	unsigned short get_path_length();
	unsigned int* get_path();
	
	private:
	std::stack<unsigned int> nodes;
	unsigned int* path;
};

#endif
