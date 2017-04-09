/* Library.hpp is the Library class specification file.*/

#include "Space.hpp"

//include guard
#ifndef LIBRARY_HPP 
#define LIBRARY_HPP

class Library : public Space
{
public:
	Library(std::string value) : Space(value) {}; //default constructor
	char menu();
	void displayTag(); 
	void displayImage(); 
};

#endif