#include <iostream>
#include <vector>
#include <unordered_map>

#include "features.h"
#include "struct.h"


/**
* @param argc number of typed arguments.
* @param argv params contents.
*/

int main(int argc, char* argv[]) {
	std::string input, output, centre;
 
	service_cmd(input, output, centre, argc, argv);
	

	if (input.empty() || output.empty()) {
		std::cout << "no parameters" << std::endl;
		
	}

	else {
		std::unordered_map <std::string, vertex> graph;  
		std::vector <std::string> unavailable; 
		

		read_data(graph, input);

		Dijkstra(graph, centre, unavailable);	

		typing_result(graph, centre, unavailable, output); 
	}
}