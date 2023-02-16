#include <iostream>
#include <cmath>      
#include <vector>
#include <unordered_map>
#include <fstream>
#include <deque>

#include "features.h"
#include "struct.h"

/**
*@file function.cpp Plik zawieraj¹cy kompletne funkcje (nag³ówek, oraz cia³o funkcji).
* 
*/

/**
* Funkcja przypisuje do zmiennej input oraz output odpowiednie parametry.
* 
* Odczytany parametr postaci "-i" informuje, ¿e kolejny argument ma byæ przypisany do "input",\n
* analogicznie z paremetrem "-o", oraz zmienn¹ "output".
* 
* @param input zmienna zawieraj¹ca nazwê pliku wejœciowego z danymi
* @param output zmienna zawieraj¹ca nazwê pliku wyjœciowego z wynikiem dzia³ania programu
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
* Funkcja odczytuje dane z pliku i zapisuje je do konteneru asocjacyjnego (unordered_map).
* 
* Dane najpierw zapisywanie s¹ do odpowiednich struktur.\n
* Je¿eli te struktury nie istniej¹ to funkcja je tworzy.\n
* Nastêpnie struktury przypisywane zostaj¹ do kontenera asocjacyjnego.
* 
* @param miasta nieuporz¹dkowany kontener asocjacyjny, do niego zapisywane s¹ struktury,
*				które zawieraj¹ informacje o konkretnych miastach.
* @param input zmienna zawieraj¹ca nazwe pliku z danymi wejœciowymi.
*/
void czytaj_plik(std::unordered_map <std::string, vertex> & miasta, std::string input) {

	std::ifstream plik(input);  
	std::string m1, m2;
	double odleg;

	if(plik) {						

		while (not plik.eof())		
		{
			plik >> m1 >> m2 >> odleg;
			miasta[m1].sasiedzi.push_back({odleg, m2});		
			miasta[m2].sasiedzi.push_back({ odleg, m1 });	

		}
	}
}
/**
* Funkcja realizuje algorytm Dijkstry.
*  
*  Warto wiedzieæ, ¿e:
*  - na pocz¹tku dzia³ania algorytmu centrala przyjmuje odleg³oœæ równ¹ zero,
*  natomiast wszystkie inne miasta przyjmuj¹ odleg³oœæ pocz¹tkow¹ równ¹ maksymalnej wartoœci typu double;
*  - domyœlnie ka¿de miasto ma przydzielon¹ wartoœæ boolowsk¹ równ¹ false w strukturze pod sk³adow¹ ("odwiedzony"),
*  oznacza to ¿e nie zosta³o ono odwiedzone przez algorytm.\n\n
* 
* Dzia³anie algorytmu:\n
*
* 1) Szukane jest najbli¿sze (wzglêdem centrali) nieodwiedzone miasto i zapisywane pod zmienn¹ ("obecny");\n
* 2) Sprawdzana jest trasa od centrali przez miasto ("obecny") do wszystkich s¹siednich miast,
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
			if (i.second.odleglosc < min and !i.second.odwiedzony) { 
				min = i.second.odleglosc;							
				obecny = i.first;			 
			}
		}									
		
		for (int j = 0; j < miasta[obecny].sasiedzi.size(); j++) {

			double dystans = miasta[obecny].odleglosc + miasta[obecny].sasiedzi[j].waga;
			std::string sasiad = miasta[obecny].sasiedzi[j].koniec;

			if (dystans < miasta[sasiad].odleglosc) {
				miasta[sasiad].odleglosc = dystans;
				miasta[sasiad].poprzedni = obecny;
			}												
		}
		miasta[obecny].odwiedzony = true;
	}
	
		for(const auto i : miasta) {  
			if (!i.second.odwiedzony) {
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
void zapisz_trasy(std::unordered_map <std::string, vertex> miasta, std::string centrala,
				  std::vector <std::string>& niedostepne, std::string output) {

	std::ofstream plik(output);

	for (const auto i : miasta) {

		if (i.second.odleglosc < max) { 

			std::deque <std::string> kolejka;

			if (i.first != centrala) { 

				std::string wczesniej;
				wczesniej = i.second.poprzedni;

				while (wczesniej != centrala) {
					kolejka.push_front(wczesniej); 
					wczesniej = miasta[wczesniej].poprzedni;
				}
				if (plik) { 

					plik << centrala << " -> ";
				
					for (int j = 0; j < kolejka.size(); j++) {
						plik << kolejka[j] << " -> ";
					}
					plik << i.first << ": " << i.second.odleglosc << std::endl;
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