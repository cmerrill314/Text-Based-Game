/* Dungeon.hpp is the Dungeon class specification file.*/

#include "Space.hpp"

//include guard
#ifndef DUNGEON_HPP 
#define DUNGEON_HPP

class Dungeon : public Space
{
public:
	Dungeon(std::string value) : Space(value) {}; //default constructor
	char menu();
	void displayTag();
	void displayImage();
};

#endif