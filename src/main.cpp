#include <iostream>
#include <fstream>
#include <string>
#include <zmq.hpp>

#include "Graph.h"
#include "GraphQuery.h"
#include "GraphDiver.h"

//  FROM ZeroMQ sample code.
//  Receive 0MQ string from socket and convert into string
static std::string s_recv (zmq::socket_t & socket) {

    zmq::message_t message;
    socket.recv(&message);

    return std::string(static_cast<char*>(message.data()), message.size());
}

//  Convert string to 0MQ string and send to socket
static bool s_send (zmq::socket_t & socket, const std::string & string) {

    zmq::message_t message(string.size());
    memcpy(message.data(), string.data(), string.size());

    bool rc = socket.send(message);
    return (rc);
}

int main() {
	std::cout << "Loading graph...";
	// Load the graph.
	Graph g("../wikimap.bin");

	if (!g.built_successfully()) {
		std::cerr << std::endl << "Error building graph.  Aborting." << std::endl;
	}

	GraphQuery gq(2, 42, 5);
	GraphDiver diver;
	GraphPath* path = diver.search(&g, gq);

	if (path == NULL) {
		std::cout << "No path found between " << gq.get_start() << " and " << gq.get_end() << std::endl;
	}
	else {
		unsigned short pathlen = path->get_path_length();
		unsigned int* numpath = path->get_path();

		std::cout << "Path length: " << pathlen << std::endl;
		std::cout << "Path found! [" << numpath[0];
		for (unsigned int i = 1; i < pathlen; i++) {
			std::cout << " => " << numpath[i];
		}
		std::cout << "]" << std::endl;
	}

	return 0;

	std::cout << "done." << std::endl;
	std::cout << "Connecting to local message queue..." << std::endl;
	zmq::context_t context(1);
	zmq::socket_t responder(context, ZMQ_REP);

	responder.connect("tcp://127.0.0.1:37253");

	std::cout << "Connected.  Awaiting clients." << std::endl;

	while (true) {
//		zmq::message_t request;
//		responder.recv(&request);
		std::string request = s_recv(responder);
		std::cout << "Received request: " << request << std::endl;
//		std::cout << "Received request" << std::endl;

		sleep(1);

//		zmq::message_t reply(5);
//		memcpy((void *)reply.data(), "World", 5);
//		responder.send(reply);
		s_send(responder, "Finished!");
	}
	/*
	if (g.built_successfully()) {
		std::cout << "Graph built.  Contains " << g.num_nodes() << " nodes." << std::endl;
		
		GraphQuery gq(0, 3, 5);
		GraphDiver diver;
		GraphPath* path = diver.search(&g, gq);
		
		if (path == NULL) {
			std::cout << "No path found between " << gq.get_start() << " and " << gq.get_end() << std::endl;
		}
		else {
			unsigned short pathlen = path->get_path_length();
			unsigned int* numpath = path->get_path();
			
			std::cout << "Path length: " << pathlen << std::endl;
			std::cout << "Path found! [" << numpath[0];
			for (unsigned int i = 1; i < pathlen; i++) {
				std::cout << " => " << numpath[i];
			}
			std::cout << "]" << std::endl;
		}
	}
	else {
		std::cout << "Error building graph." << std::endl;
	}*/

}
