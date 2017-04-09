/* Tower.hpp is the Tower class specification file.*/

#include "Space.hpp"

//include guard
#ifndef TOWER_HPP 
#define TOWER_HPP

class Tower : public Space
{
public:
	Tower(std::string value) : Space(value) {}; //default constructor
	char menu();
	void displayTag(); 
	void displayImage(); 
};

#endif