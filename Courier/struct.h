#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

/**
* @file struct.h Plik zawieraj¹cy struktury oraz zmienn¹ globaln¹.
* 
* @param max wartoœæ odpowiadaj¹ca nieskoñczonoœci.
*/
const double max = std::numeric_limits<double>::max();


/** Struktura przechowuje informacje o danym s¹siednim mieœcie.
* 
* @param waga odleg³oœæ pomiêdzy miastami (d³ugoœæ krawêdzi).
* @param koniec s¹siednie miasto, czyli koniec krawêdzi.
*/

struct krawedz {			
	double waga;			
	std::string koniec;		
};


/** Struktura przechowuje informacje o danym mieœcie.
* 
* @param poprzedni poprzednie miasto wyznaczone na podstawie algorytmu Dijkstry.
* @param odleglosc odleg³oœæ od miasta pocz¹tkowego.
* @param sasiedzi wektor struktur s¹siednich miast.
* @param odwiedzony wartoœæ boolowska, informuj¹ca nas czy dany wierzcho³ek zosta³ odwiedzony.
*/

struct vertex {

	std::string previous;	
	double distance = max; 
	std::vector <krawedz> neighbour;  
	bool visited = false; 
};