#include <iostream>
#include <cmath>      
#include <vector>
#include <unordered_map>
#include <fstream>
#include <deque>

#include "function.h"
#include "struct.h"

/**
*	\mainpage Introduction
*   
*			<strong>This program create route file from central city to all other cities. 
*			If params aren't complete, the program will show an information about lacking params</strong>
* 
*	@section Manual
*	1) Pobierz plik "projekt" z mojego repozytorium na GitHub;\n
*	2) Urochom wiersz poleceñ; \n
*	3) Korzystaj¹c z polecenia 'cd' wejdŸ kolejno do plików "projekt", "x64", "Debug"; \n
*	4) Nastêpnie uruchom program wpisuj¹c argumenty z podpunktu nr.5
*	   (pamiêtaj ¿eby zamiast "input.txt" wpisaæ nazwê pliku z danymi. Natomiast output.txt mo¿esz zast¹piæ dowolnie nazwanym plikiem txt); \n
*	5) projekt.exe -i input.txt -o output.txt; \n
*	6) Podaj miasto w którym bêdzie centrala.
* 
*   @author <strong>Karol Pitera</strong>
*	@date <strong>03.02.2023</strong>
*/

/**
* @file main.cpp Plik zawieraj¹cy funkcje g³ówn¹.
*  
*
* @param argc liczba podanych argumentów.
* @param argv zawartoœæ parametrów.
*/

int main(int argc, char* argv[]) {
	std::string input;
	std::string output;
 
	obsluga_terminala(input, output, argc, argv);

	if (input.empty() || output.empty()) {
		std::cout << "brak odpowiednich parametrow" << std::endl;
		
	}

	else {
		std::unordered_map <std::string, wierzcholek> miasta;  
		std::vector <std::string> niedostepne; 
		std::string centrala;

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
			std::cin >> centrala;
			std::cout << std::endl;
		
			for (const auto i : miasta) {

				if (i.first == centrala) {
					istnieje = true;
				}
			}	
		if (!istnieje)
				std::cout << "Nie znaleziono takiego miasta, podaj poprawna nazwe: ";

		} while (!istnieje);
		miasta[centrala].odleglosc = 0;			

		Dijkstra(miasta, niedostepne);	

		zapisz_trasy(miasta, centrala, niedostepne, output); 
	}
}