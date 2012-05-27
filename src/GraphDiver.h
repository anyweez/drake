#include "Graph.h"
#include "GraphPath.h"
#include "GraphQuery.h"

#ifndef GRAPHDIVER_H
#define GRAPHDIVER_H

class GraphDiver {
	public:
		GraphDiver();
		~GraphDiver();
		
		GraphPath* search(Graph* graph, GraphQuery& query);
		
	private:
		GraphPath* _search(Graph* graph, GraphQuery& query, unsigned int loc, unsigned short depth);
};

#endif
