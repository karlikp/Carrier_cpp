#include <iostream>
#include <cmath>      
#include <vector>
#include <unordered_map>
#include <fstream>
#include <deque>

#include "features.h"
#include "struct.h"

/**
*@file features.cpp complete features file (header, and feature body).
* 
*/

/**
* Feature assign a proper params to variables input and output.
* 
* Param "-i" inform the feature that a next argument will be assign to the variable "input".
* The program will do similar with a param "-o", and the variable "output".
* 
* @param input the variable includes a input file name with data
* @param output the variable includes output file name with a program result 
*/

void service_cmd(std::string & input, std::string& output, int argc, char* argv[]) {
	for (int i = 0; argc > i; i++)
	{
		if (strcmp(argv[i], "-i") == 0) {
			input = argv[i + 1];
		}
		if (strcmp(argv[i], "-o") == 0) {
			output = argv[i + 1];
		}
	}	
}

/**
* Feature reads a data from a data file and writes it to the unordered map.
* 
* First, Data are saved to proper structures \n
* If the structures don't exist then the feature creates them.\n
* Second, Structures are saved to the unordered map.
* 
* @param cities unordered map, include structures with a information about cities from the database
* @param input the variable includes a file name with input data.
*/
void read_data(std::unordered_map <std::string, vertex> & cities, std::string input) {

	std::ifstream plik(input);  
	std::string m1, m2;
	double dist;

	if(plik) {						

		while (not plik.eof())		
		{
			plik >> m1 >> m2 >> dist;
			cities[m1].neighbors.push_back({dist, m2});		
			cities[m2].neighbors.push_back({ dist, m1 });	

		}
	}
}
/**
* The feature executes the Dijkstra algorithm
*  
*  Good to know, that at the beginning of the program:
* 
*  - The city which was choosen the center is assigned the value zero.
*	 Whereas all other cities is assigned the distance variable equal to a maximal posible value;
*  - Every city includes a bool value equal to "false" in the structure variable called "visited",
*	 (The value "false" means that given city hasn't been visited by algorithm .\n\n
* 
* The algorithm executuion:\n
*
* 1) The closest unvisited city (from center) is serached and saved to a variable called "current";\n
* 2) The routes from center to all other cities are cheacked,
*	 If the distance are shorter than current saved way,
*    the distance is overwritten and city from variable "current" are assigned to structure variable "previaus";\n
* 3) Then city from the variable "current" is marked as visited, and value true is assigned to variable "visited" of structere given city;\n
* 4) The points from 1 to 3 are executed as many time as there are saved a cities in the container (unordered_map);\n
* 5) The unvisited cities are saved in the vector called "unavailable".
* 
* @param cities The unordered map, there are saved the cities structures, with information about a given cities. 
* @param unavailable The cities, which haven't got any route connecting to the center.
*/
void Dijkstra(std::unordered_map <std::string, vertex> & cities, std::vector <std::string> & unavailable) {
	
	for (int k = 0; k < cities.size(); k++) {
		double min = max;
		std::string current;

		for (const auto i : cities) {
			if (i.second.distance < min and !i.second.visited) { 
				min = i.second.distance;							
				current = i.first;			 
			}
		}									
		
		for (int j = 0; j < cities[current].neighbors.size(); j++) {

			double current_way = cities[current].distance + cities[current].neighbors[j].range;
			std::string neighbour = cities[current].neighbors[j].end;

			if (current_way < cities[neighbour].distance) {
				cities[neighbour].distance = current_way;
				cities[neighbour].previous = current;
			}												
		}
		cities[current].visited = true;
	}
	
		for(const auto i : cities) {  
			if (!i.second.visited) {
				unavailable.push_back(i.first); 
			}
		}
}
/** 
* The feature sorts the cities and previous citis, then the feature saves the program result to the new create file. 
* 
* 1) A queue is created, then next city and previous cities are saved to the first position the queue until the center is saved;\n
* 2) Then, Route from the center, through previous cities and finished on the last city (saved in the variable "i"),
*	 the distence information is saved in the end;\ 
* 3) The points from 1 to 2 are performed for each city from the unordered map;\n
* 4) All cities which haven't got conected with the center are saved type in to the file with a short information (about not connected);\n
* 5) The file is closed.\n
*
* @param cities The unordered map, there are saved the cities structures, with information about a given cities.
* @param center A city that chose as the center. 
* @param unavailable The cities, which haven't got any route connecting to the center.
* @param output the variable includes output file name with a program result 
*/
void typing_route(std::unordered_map <std::string, vertex> cities, std::string center,
				  std::vector <std::string>& unavailable, std::string output) {

	std::ofstream file(output);

	for (const auto i : cities) {

		if (i.second.distance < max) { 

			std::deque <std::string> queue;

			if (i.first != center) { 

				std::string last;
				last = i.second.previous;

				while (last != center) {
					queue.push_front(last); 
					last = cities[last].previous;
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