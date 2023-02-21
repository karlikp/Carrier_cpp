#include <iostream>
#include <cmath>      
#include <vector>
#include <unordered_map>
#include <fstream>
#include <deque>

#include "features.h"
#include "struct.h"

/**
*@file function.cpp complete features file (header, and feature body).
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
* @param miasta unordered map, include structures with a information about cities from the database
* @param input the variable includes a file name with input data.
*/
void read_data(std::unordered_map <std::string, vertex> & miasta, std::string input) {

	std::ifstream plik(input);  
	std::string m1, m2;
	double dist;

	if(plik) {						

		while (not plik.eof())		
		{
			plik >> m1 >> m2 >> dist;
			miasta[m1].neighbour.push_back({dist, m2});		
			miasta[m2].neighbour.push_back({ dist, m1 });	

		}
	}
}
/**
* The feature executes the Dijkstra algorithm
*  
*  Good to know, that at the beginning of the program:
*  - The central variable is assigned the value zero.
*	 Whereas all other cities is assigned the distance variable equal to a maximal posible value;
*  - Every city includes a bool value equal to "false" in the structure variable called "visited",
*	 (The value "false" means that given city hasn't been visited by algorithm .\n\n
* 
* The algorithm executuion:\n
*
* 1) The closest unvisited city (from center) is serached and saved to a variable called "current";\n
* 
* 2) The routes from center to all other cities are cheacked,
*	If the distance are shorter than current saved way, the distance is overwritten and city from variable "current" are assigned to structure variable "previaus"

Sprawdzana jest trasa od centrali przez miasto ("obecny") do wszystkich s¹siednich miast,
*	 je¿eli odleg³oœæ oka¿e siê krótsza ni¿ ta, która jest zapisana do danego miasta wtedy 
*	 odleg³oœæ jest nadpisywana, oraz do "poprzedni" (sk³adowej struktury miasta s¹siedniego) przypisywane jest miasto ("obecny");\n
* 3) Odznaczamy miasto ("obecny") jako zbadane przez przypisanie jego sk³adowej ("odwiedzone")\n wartoœci = true;\n
* 4) Operacje od 1 do 3 wykonujemy tyle razy ile jest ró¿nych miast w kontenerze asocjacyjnym;\n
* 5) Miasta które nie zosta³y odwiedzone zapisujemy w wektorze ("niedostepne").
* 
* @param miasta nieuporz¹dkowany kontener asocjacyjny, do niego zapisywane s¹ struktury,
*				które zawieraj¹ informacje o konkretnych miastach.
* @param niedostepne miasta, które nie maj¹ trasy ³¹cz¹cej z central¹.
*/
void Dijkstra(std::unordered_map <std::string, vertex> & miasta, std::vector <std::string> & niedostepne) {
	
	for (int k = 0; k < miasta.size(); k++) {
		double min = max;
		std::string obecny;

		for (const auto i : miasta) {
			if (i.second.distance < min and !i.second.visited) { 
				min = i.second.distance;							
				obecny = i.first;			 
			}
		}									
		
		for (int j = 0; j < miasta[obecny].neighbour.size(); j++) {

			double dystans = miasta[obecny].distance + miasta[obecny].neighbour[j].waga;
			std::string sasiad = miasta[obecny].neighbour[j].koniec;

			if (dystans < miasta[sasiad].distance) {
				miasta[sasiad].distance = dystans;
				miasta[sasiad].previous = obecny;
			}												
		}
		miasta[obecny].visited = true;
	}
	
		for(const auto i : miasta) {  
			if (!i.second.visited) {
				niedostepne.push_back(i.first); 
			}
		}
}
/** 
* Funkcja sortuje miasta i poprzedników oraz zapisuje podsumowane trasy do nowo utworzonego pliku. 
* 
* 1) Tworzona jest kolejka do której na pierwsz¹ pozycje zapisywane s¹ kolejne poprzednie miasta
*	do momentu dojœcia do centrali (która nie jest zapisywana do kolejki);\n
* 2) Do utworzonego pliku zapisywana jest trasa od centrali przez poprzedników do miasta,
*   które w tej iteracji jest zapisane pod zmienn¹ 'i'.
*	Po wypisanych miastach dopisywana jest podsumowana odleg³oœæ trasy;\n
* 3) Punkty od 1 do 2 wykonujemy dla ka¿dego miasta w kontenerze asocjacyjnym;\n
* 4) Do utworzonego pliku po krótkim opisie zapisywane s¹ wszystkie miasta, które nie maj¹ po³¹czenia z central¹;\n
* 5) Plik zostaje zamkniêty.\n
*
* @param miasta nieuporz¹dkowany kontener asocjacyjny, który zawiera struktury przechowuj¹ce informacje o konkretnych miastach.
* @param centrala miasto które zosta³o wyznaczone na centrale.
* @param niedostepne miasta, które nie maj¹ trasy ³¹cz¹cej z central¹.
* @param output zmienna zawieraj¹ca nazwê pliku wyjœciowego z wynikiem dzia³ania programu.
*/
void typing_route(std::unordered_map <std::string, vertex> miasta, std::string centrala,
				  std::vector <std::string>& niedostepne, std::string output) {

	std::ofstream plik(output);

	for (const auto i : miasta) {

		if (i.second.distance < max) { 

			std::deque <std::string> kolejka;

			if (i.first != centrala) { 

				std::string wczesniej;
				wczesniej = i.second.previous;

				while (wczesniej != centrala) {
					kolejka.push_front(wczesniej); 
					wczesniej = miasta[wczesniej].previous;
				}
				if (plik) { 

					plik << centrala << " -> ";
				
					for (int j = 0; j < kolejka.size(); j++) {
						plik << kolejka[j] << " -> ";
					}
					plik << i.first << ": " << i.second.distance << std::endl;
				}
			}
		}
	}
	if (niedostepne.size() > 0) {
		plik << std::endl << "Miasta nie majace polaczenia z centrala: " << std::endl;
	
		for (int i = 0; i < niedostepne.size(); i++) {
			plik << "- " << niedostepne[i] << std::endl;	
		}
	}
	plik.close();
}