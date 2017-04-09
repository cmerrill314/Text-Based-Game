/* GrandHall.hpp is the GrandHall class specification file.*/

#include "Space.hpp"

//include guard
#ifndef GRANDHALL_HPP 
#define GRANDHALL_HPP

class GrandHall : public Space
{
public:
	GrandHall(std::string value) : Space(value) {}; //default constructor
	char menu();
	void displayTag();
	void displayImage(); 
};

#endif