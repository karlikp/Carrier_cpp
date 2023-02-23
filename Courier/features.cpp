#include <iostream>
#include <cmath>      
#include <vector>
#include <unordered_map>
#include <fstream>
#include <deque>

#include "features.h"
#include "struct.h"

/**
*@file features.cpp complete features file
* 
*/

/**
* Feature assign a proper params to variables input, output and centre.
* 
* @param input the variable includes a input file name with data
* @param output the variable includes output file name with a program result
* @param centre The varaible includes name of central city
*/

void service_cmd(std::string & input, std::string & output, std::string & centre, int argc, char* argv[]) {
	for (int i = 0; argc > i; i++)
	{
		if (strcmp(argv[i], "-i") == 0) {
			input = argv[i + 1];
		}
		if (strcmp(argv[i], "-o") == 0) {
			output = argv[i + 1];
		}
		if (strcmp(argv[i], "-c") == 0) {
			centre = argv[i + 1];
		}
	}	
}

/**
* Feature reads a information from a data file and save the data to the map.
* 
* The map includes structures with information about cities. 
* 
* @param graph unordered map, which is indexed with city names.
* @param input the variable includes a file name with input data.
*/
void read_data(std::unordered_map <std::string, vertex> & graph, std::string input) {

	std::ifstream plik(input);  
	std::string m1, m2;
	double distance;

	if(plik) {						

		while (not plik.eof())		
		{
			plik >> m1 >> m2 >> distance;
			graph[m1].neighbors.push_back({distance, m2});		
			graph[m2].neighbors.push_back({ distance, m1 });	

		}
	}
}
/**
* The feature searches the shortest routes from the central city to all different cities.
* 
* @param graph unordered map, which is indexed with city names.
* @param unavailable The cities, which haven't got any route connecting to the center.
*/

void Dijkstra(std::unordered_map <std::string, vertex> & graph, std::string & centre, std::vector <std::string> & unavailable) {


	graph[centre].distance = 0;
	
	for (int k = 0; k < graph.size(); k++) {
		double min = std::numeric_limits<double>::max();
		std::string current;

		for (const auto i : graph) {
			if (i.second.distance < min and !i.second.visited) { 
				min = i.second.distance;							
				current = i.first;			 
			}
		}									
		
		for (int j = 0; j < graph[current].neighbors.size(); j++) {

			double current_way = graph[current].distance + graph[current].neighbors[j].range;
			std::string neighbour = graph[current].neighbors[j].end;

			if (current_way < graph[neighbour].distance) {
				graph[neighbour].distance = current_way;
				graph[neighbour].previous = current;
			}												
		}
		graph[current].visited = true;
	}
	
		for(const auto i : graph) {  
			if (!i.second.visited) {
				unavailable.push_back(i.first); 
			}
		}
}
/** 
* The feature sorts the cities and previous citis, and saves the program result to the new create file. 
* 
* When the function finished sort, then all cities visited in one route are typed in the right order with finish distance.
* 
* @param graph unordered map, which is indexed with city names.
* @param centre The varaible includes name of central city
* @param unavailable The cities, which haven't got any route connecting to the center.
* @param output the variable includes output file name with a program result 
*/
void typing_result(std::unordered_map <std::string, vertex> graph, std::string center,
				  std::vector <std::string>& unavailable, std::string output) {

	std::ofstream file(output);

	for (const auto i : graph) {

		if (i.second.distance < std::numeric_limits<double>::max()) { 

			std::deque <std::string> queue;

			if (i.first != center) { 

				std::string last;
				last = i.second.previous;

				while (last != center) {
					queue.push_front(last); 
					last = graph[last].previous;
				}
				if (file) { 

					file << center << " -> ";
				
					for (int j = 0; j < queue.size(); j++) {
						file << queue[j] << " -> ";
					}
					file << i.first << ": " << i.second.distance << std::endl;
				}
			}
		}
	}
	if (unavailable.size() > 0) {
		file << std::endl << "Cities without connecting to the center: " << std::endl;
	
		for (int i = 0; i < unavailable.size(); i++) {
			file << "- " << unavailable[i] << std::endl;	
		}
	}
	file.close();
}