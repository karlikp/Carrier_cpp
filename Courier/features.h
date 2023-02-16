#pragma once

#include <iostream>
#include <cmath>      
#include <vector>
#include <unordered_map>
#include <fstream>

#include "struct.h"
/**
* @file features.h Plik zawierający nagłówki funkcji.
*/
void service_cmd(std::string& input, std::string& output, int argc, char* argv[]);

void read_data(std::unordered_map <std::string, vertex> & miasta, std::string input);

void Dijkstra(std::unordered_map <std::string, vertex> & miasta, std::vector <std::string> & niedostepne);

void typing_route(std::unordered_map <std::string, vertex> miasta, std::string centrala, std::vector <std::string>& niedostepne, 
				  std::string output);
