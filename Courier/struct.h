#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

/**
* @file struct.h Plik zawieraj�cy struktury oraz zmienn� globaln�.
* 
* @param max warto�� odpowiadaj�ca niesko�czono�ci.
*/
const double max = std::numeric_limits<double>::max();


/** Struktura przechowuje informacje o danym s�siednim mie�cie.
* 
* @param waga odleg�o�� pomi�dzy miastami (d�ugo�� kraw�dzi).
* @param koniec s�siednie miasto, czyli koniec kraw�dzi.
*/

struct krawedz {			
	double waga;			
	std::string koniec;		
};


/** Struktura przechowuje informacje o danym mie�cie.
* 
* @param poprzedni poprzednie miasto wyznaczone na podstawie algorytmu Dijkstry.
* @param odleglosc odleg�o�� od miasta pocz�tkowego.
* @param sasiedzi wektor struktur s�siednich miast.
* @param odwiedzony warto�� boolowska, informuj�ca nas czy dany wierzcho�ek zosta� odwiedzony.
*/

struct vertex {

	std::string previous;	
	double distance = max; 
	std::vector <krawedz> neighbour;  
	bool visited = false; 
};