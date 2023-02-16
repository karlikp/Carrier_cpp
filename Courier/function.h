#pragma once

#include <iostream>
#include <cmath>      
#include <vector>
#include <unordered_map>
#include <fstream>

#include "struct.h"
/**
* @file function.h Plik zawieraj¹cy nag³ówki funkcji.
*/
void obsluga_terminala(std::string& input, std::string& output, int argc, char* argv[]);

void czytaj_plik(std::unordered_map <std::string, wierzcholek> & miasta, std::string input);

void Dijkstra(std::unordered_map <std::string, wierzcholek> & miasta, std::vector <std::string> & niedostepne);

void zapisz_trasy(std::unordered_map <std::string, wierzcholek> miasta, std::string centrala, std::vector <std::string>& niedostepne, 
				  std::string output);
