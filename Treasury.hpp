/* Treasury.hpp is the Treasury class specification file.*/

#include "Space.hpp"

//include guard
#ifndef TREASURY_HPP 
#define TREASURY_HPP

class Treasury : public Space
{
public:
	Treasury(std::string value) : Space(value) {}; //default constructor
	char menu();
	void displayTag(); 
	void displayImage(); 
};

#endif