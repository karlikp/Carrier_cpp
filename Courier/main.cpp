#include <iostream>
#include <cmath>      
#include <vector>
#include <unordered_map>
#include <fstream>
#include <deque>

#include "features.h"
#include "struct.h"

/**
*	\mainpage Introduction
*   
*	<strong>This program create a file with routes between company centre to all other cities. </strong>
* 
*	@section Manual
*	1) Download all files from my repository called Courier_cpp on the GitHub;\n
*	2) Launch command prompt; \n
*	3) Use command 'cd' and go to files "Courier_cpp",  "Courier", "x64", "Debug"; \n
*	4) Then type in arguments from point at the number 5.; \n
*	5) Courier.exe -i input.txt -o output.txt -c centre;
*	(Remember that instead input.txt, output.txt and centre type in proper params)\n
*	For examples: Courier.exe -i data_file.txt -o answer_file.txt -c Poznan
* 
*   @author <strong>Karol Pitera</strong>
*	@date <strong>23.02.2023</strong>
*/

/**
* @file main.cpp File with main feature.
*  
*
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

	/*	std::cout << "The program calculate the shortest route between centre and all different cities" << std::endl << std::endl;
		std::cout << "Availble cities: " << std::endl;

		for (const auto i : cities) {			
			std::cout << "- " << i.first << std::endl;
		}

		std::cout << std::endl << "Type city name where should the centre be: "; 
		bool exist = false;
		do
		{
			std::cin >> centre;
			std::cout << std::endl;
		
			for (const auto i : cities) {

				if (i.first == centre) {
					exist = true;
				}
			}	
			if (!exist)
				std::cout << "This city was not found, type in correct a city name: ";

		} while (!exist);
		graph[centre].distance = 0;	
		*/

		Dijkstra(graph, centre, unavailable);	

		typing_result(graph, centre, unavailable, output); 
	}
}