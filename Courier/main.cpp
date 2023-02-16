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
*			<strong>This program create route file from central city to all other cities. 
*			If params aren't complete, the program will show an information about lacking params</strong>
* 
*	@section Manual
*	1) Download all files from my repository on the GitHub;\n
*	2) Launch command prompt; \n
*	3) Use command 'cd' and go to files "projekt", "x64", "Debug"; \n
*	4) Then type in arguments from point at the number 5.
*	   (Remember that instead input.txt" type in data file name. ; \n
*	5) projekt.exe -i input.txt -o output.txt; \n
*	6) Choose a city where should the central be.
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
		std::unordered_map <std::string, vertex> miasta;  
		std::vector <std::string> unavailable; 
		std::string central;

		czytaj_plik(miasta, input);

		std::cout << "Program oblicza najkrotsza trase miedzy centrala a miastem do ktorego trzeba dostarczyc paczke" << std::endl << std::endl;
		std::cout << "Dostepne miasta: " << std::endl;

		for (const auto i : miasta) {			
			std::cout << "- " << i.first << std::endl;
		}

		std::cout << std::endl << "Wpisz nazwe miasta w ktorym ma znajdowac sie centrala: "; 
		bool istnieje = false;
		do
		{
			std::cin >> central;
			std::cout << std::endl;
		
			for (const auto i : miasta) {

				if (i.first == central) {
					istnieje = true;
				}
			}	
		if (!istnieje)
				std::cout << "Nie znaleziono takiego miasta, podaj poprawna nazwe: ";

		} while (!istnieje);
		miasta[central].odleglosc = 0;			

		Dijkstra(miasta, unavailable);	

		zapisz_trasy(miasta, central, unavailable, output); 
	}
}