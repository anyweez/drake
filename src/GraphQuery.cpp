#include "GraphQuery.h"

GraphQuery::GraphQuery(unsigned int start, unsigned int end, unsigned int depth_limit) {
	this->start = start;
	this->end = end;
	this->depth_limit = depth_limit;
}

GraphQuery::~GraphQuery() {
	
}


unsigned int GraphQuery::get_start() {
	return this->start;
}

unsigned int GraphQuery::get_end() {
	return this->end;
}

unsigned short GraphQuery::get_depth_limit() {
	return this->depth_limit;
}
