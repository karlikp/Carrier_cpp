#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

/**
* @file struct.h Structures file.
*/


/** The scructure includes a information about a given neighbouring city.
* 
* @param range The distance between the cities.
* @param end Neighbouring city.
*/

struct edge {			
	double range;			
	std::string end;		
};


/** The structure include a information about the given city.
* 
* @param previous The earlier city that was determined by the algorithm
* @param distance Dictance from the given city to the center.
* @param neighbors Vector of nieghbouring cities stcrutures.
* @param visited Bool value, that include the information about visiting the city.
*/

struct vertex {

	double distance = std::numeric_limits<double>::max();
	std::string previous; ;
	std::vector <edge> neighbors;  
	bool visited = false; 
};