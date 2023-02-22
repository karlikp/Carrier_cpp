#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

/**
* @file struct.h Structures file.
* 
* @param max The maximal value mean a infinity
*/
const double max = std::numeric_limits<double>::max();


/** The scructure includes a information about a given neighbouring city.
* 
* @param range The distance between the cities.
* @param end neighbouring city.
*/

struct edge {			
	double range;			
	std::string end;		
};


/** The structure include a information about the given city.
* 
* @param previous The previous city that was chose by Dijkstra algorithm.
* @param distance Dictance from the given city to the center.
* @param neighbors Vector of nieghbouring cities stcrutures.
* @param visited Bool value, that include the information about visiting the city.
*/

struct vertex {

	std::string previous;	
	double distance = max; 
	std::vector <edge> neighbors;  
	bool visited = false; 
};