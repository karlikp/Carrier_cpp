#ifndef FEATURES_H
#define FEATURES_H

#include <vector>
#include <string>
#include <unordered_map>

#include "struct.h"

void service_cmd(std::string& input, std::string& output, std::string & centre, int argc, char* argv[]);

void read_data(std::unordered_map <std::string, vertex> & graph, std::string input);

void Dijkstra(std::unordered_map <std::string, vertex> & graph, std::string & centre, std::vector <std::string> & unavailable);

void typing_result(std::unordered_map <std::string, vertex> graph, std::string center, std::vector <std::string>& unavailable,
				  std::string output);

#endif