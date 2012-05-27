#ifndef GRAPHQUERY_H
#define GRAPHQUERY_H

class GraphQuery {
	public:
	GraphQuery(unsigned int start, unsigned int end, unsigned int depth_limit);
	~GraphQuery();
	
	unsigned int get_start();
	unsigned int get_end();
	unsigned short get_depth_limit();
	
	private:
	unsigned int start;
	unsigned int end;
	unsigned short depth_limit;
};

#endif
