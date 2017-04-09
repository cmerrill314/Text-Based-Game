/* Chambers.hpp is the Chambers class specification file.*/

#include "Space.hpp"

//include guard
#ifndef CHAMBERS_HPP 
#define CHAMBERS_HPP

class Chambers : public Space
{
public:
	Chambers(std::string value) : Space(value) {}; //default constructor
	char menu();
	void displayTag();
	void displayImage();
};

#endif