#include <iostream>
#include <cmath>      
#include <vector>
#include <unordered_map>
#include <fstream>
#include <deque>

#include "features.h"
#include "struct.h"

/**
*@file function.cpp Plik zawieraj�cy kompletne funkcje (nag��wek, oraz cia�o funkcji).
* 
*/

/**
* Funkcja przypisuje do zmiennej input oraz output odpowiednie parametry.
* 
* Odczytany parametr postaci "-i" informuje, �e kolejny argument ma by� przypisany do "input",\n
* analogicznie z paremetrem "-o", oraz zmienn� "output".
* 
* @param input zmienna zawieraj�ca nazw� pliku wej�ciowego z danymi
* @param output zmienna zawieraj�ca nazw� pliku wyj�ciowego z wynikiem dzia�ania programu
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
* Dane najpierw zapisywanie s� do odpowiednich struktur.\n
* Je�eli te struktury nie istniej� to funkcja je tworzy.\n
* Nast�pnie struktury przypisywane zostaj� do kontenera asocjacyjnego.
* 
* @param miasta nieuporz�dkowany kontener asocjacyjny, do niego zapisywane s� struktury,
*				kt�re zawieraj� informacje o konkretnych miastach.
* @param input zmienna zawieraj�ca nazwe pliku z danymi wej�ciowymi.
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
*  Warto wiedzie�, �e:
*  - na pocz�tku dzia�ania algorytmu centrala przyjmuje odleg�o�� r�wn� zero,
*  natomiast wszystkie inne miasta przyjmuj� odleg�o�� pocz�tkow� r�wn� maksymalnej warto�ci typu double;
*  - domy�lnie ka�de miasto ma przydzielon� warto�� boolowsk� r�wn� false w strukturze pod sk�adow� ("odwiedzony"),
*  oznacza to �e nie zosta�o ono odwiedzone przez algorytm.\n\n
* 
* Dzia�anie algorytmu:\n
*
* 1) Szukane jest najbli�sze (wzgl�dem centrali) nieodwiedzone miasto i zapisywane pod zmienn� ("obecny");\n
* 2) Sprawdzana jest trasa od centrali przez miasto ("obecny") do wszystkich s�siednich miast,
*	 je�eli odleg�o�� oka�e si� kr�tsza ni� ta, kt�ra jest zapisana do danego miasta wtedy 
*	 odleg�o�� jest nadpisywana, oraz do "poprzedni" (sk�adowej struktury miasta s�siedniego) przypisywane jest miasto ("obecny");\n
* 3) Odznaczamy miasto ("obecny") jako zbadane przez przypisanie jego sk�adowej ("odwiedzone")\n warto�ci = true;\n
* 4) Operacje od 1 do 3 wykonujemy tyle razy ile jest r�nych miast w kontenerze asocjacyjnym;\n
* 5) Miasta kt�re nie zosta�y odwiedzone zapisujemy w wektorze ("niedostepne").
* 
* @param miasta nieuporz�dkowany kontener asocjacyjny, do niego zapisywane s� struktury,
*				kt�re zawieraj� informacje o konkretnych miastach.
* @param niedostepne miasta, kt�re nie maj� trasy ��cz�cej z central�.
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
* Funkcja sortuje miasta i poprzednik�w oraz zapisuje podsumowane trasy do nowo utworzonego pliku. 
* 
* 1) Tworzona jest kolejka do kt�rej na pierwsz� pozycje zapisywane s� kolejne poprzednie miasta
*	do momentu doj�cia do centrali (kt�ra nie jest zapisywana do kolejki);\n
* 2) Do utworzonego pliku zapisywana jest trasa od centrali przez poprzednik�w do miasta,
*   kt�re w tej iteracji jest zapisane pod zmienn� 'i'.
*	Po wypisanych miastach dopisywana jest podsumowana odleg�o�� trasy;\n
* 3) Punkty od 1 do 2 wykonujemy dla ka�dego miasta w kontenerze asocjacyjnym;\n
* 4) Do utworzonego pliku po kr�tkim opisie zapisywane s� wszystkie miasta, kt�re nie maj� po��czenia z central�;\n
* 5) Plik zostaje zamkni�ty.\n
*
* @param miasta nieuporz�dkowany kontener asocjacyjny, kt�ry zawiera struktury przechowuj�ce informacje o konkretnych miastach.
* @param centrala miasto kt�re zosta�o wyznaczone na centrale.
* @param niedostepne miasta, kt�re nie maj� trasy ��cz�cej z central�.
* @param output zmienna zawieraj�ca nazw� pliku wyj�ciowego z wynikiem dzia�ania programu.
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