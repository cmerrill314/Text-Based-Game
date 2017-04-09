/* Space.hpp is the Space class specification file.*/

#include <string>
#include <list>
#include <iostream>
#include <fstream>
using namespace std;

//include guard
#ifndef SPACE_HPP 
#define SPACE_HPP

class Space
{
protected:
	//location pointers:
	Space* right;
	Space* left;
	Space* up;
	Space* down;

	//space properties:
	std::string name;       //room name
	bool lightsOn;          //are the lights on
	bool specItemObt;       //is the special item obtained
	bool reqItemObt;        //is the required item obtained
	bool treasuryUnlocked;  //is the treasury unlocked
	bool healthPotionFound; //has the health potion been found

public:
	Space(std::string);

	//shared virtual functions:
	virtual char menu() = 0;         //manages the room's menu
	virtual void displayTag() = 0;   //displays the room's tagline
	virtual void displayImage() = 0; //displays the room's image

	//getter functions:
	Space* getRight() { return right; };
	Space* getLeft() { return left; };
	Space* getUp() { return up; };
	Space* getDown() { return down; };
	std::string getName() { return name; };
	bool getSpecItemObt() { return specItemObt; };
	bool getTreasuryUnlocked() { return treasuryUnlocked; };
	bool getHealthPotionFound() { return healthPotionFound; };

	//setter functions:
	void setPointer(char, Space*);
	void setLightsOn(bool val) { this->lightsOn = val; };
	void setSpecItemObt(bool val) { this->specItemObt = val; };
	void setReqItemObt(bool val) { this->reqItemObt = val; };
	void setTreasuryUnlocked(bool val) { this->treasuryUnlocked = val; };
	void setHealthPotionFound(bool val) { this->healthPotionFound = val; };

	//input validation
	int getInteger(std::string);
};

#endif