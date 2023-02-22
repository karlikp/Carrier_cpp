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
*			<strong>This program create route file from a centre city to all other cities. 
*			If the params aren't complete, the program will show an information about lacking params</strong>
* 
*	@section Manual
*	1) Download all files from my repository on the GitHub;\n
*	2) Launch command prompt; \n
*	3) Use command 'cd' and go to files "projekt", "x64", "Debug"; \n
*	4) Then type in arguments from point at the number 5.
*	   (Remember that instead input.txt" type in data file name. ; \n
*	5) Courier.exe -i input.txt -o output.txt; \n
*	6) Choose a city where should the centre be.
* 
*   @author <strong>Karol Pitera</strong>
*	@date <strong>16.02.2023</strong>
*/

/**
* @file main.cpp File with main feature.
*  
*
* @param argc number of typed arguments.
* @param argv params contents.
*/

int main(int argc, char* argv[]) {
	std::string input;
	std::string output;
 
	service_cmd(input, output, argc, argv);

	if (input.empty() || output.empty()) {
		std::cout << "no parameters" << std::endl;
		
	}

	else {
		std::unordered_map <std::string, vertex> cities;  
		std::vector <std::string> unavailable; 
		std::string centre;

		read_data(cities, input);

		std::cout << "The program calculate the shortest route between centre and all different cities" << std::endl << std::endl;
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
		cities[centre].distance = 0;			

		Dijkstra(cities, unavailable);	

		typing_route(cities, centre, unavailable, output); 
	}
}