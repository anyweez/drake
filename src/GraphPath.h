#ifndef GRAPHPATH_H
#define GRAPHPATH_H

#include <list>

class GraphPath {
	public:
	GraphPath(unsigned int node_id);
	~GraphPath();
	
	void add(unsigned int node_id);
	unsigned short get_path_length();
	unsigned int* get_path();
	
	private:
	void compress_path();
	
	std::list<unsigned int> nodes;
	unsigned int* path;
	bool compressed;
};

#endif
