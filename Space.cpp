#include "Space.hpp"

/*********************************************************************
** Function: Space::Space
**
** Description: Constructor for the Space class. Sets the room name, 
** initializes the pointer vvariables to NULL and initializes all of 
** the bool variables to false. 
**
** Parameters: A string value which represents the name of the room. 
*********************************************************************/
Space::Space(std::string val)
{
	//set each room's name
	if (val == "GRAND HALL")
		this->name = val;
	else if (val == "KING'S CHAMBERS")
		this->name = val;
	else if (val == "LIBRARY")
		this->name = val;
	else if (val == "HIDDEN TREASURY")
		this->name = val;
	else if (val == "DUNGEON")
		this->name = val;
	else if (val == "TOWER")
		this->name = val;

	//initialize all location pointers to NULL
	this->up = NULL;
	this->down = NULL;
	this->right = NULL;
	this->left = NULL;

	//initialize all game variables to false
	this->lightsOn = false;
	this->specItemObt = false;
	this->reqItemObt = false;
	this->healthPotionFound = false;
	this->treasuryUnlocked = false;
}

/*********************************************************************
** Function: Space::setPointer
**
** Description: Sets one of the four pointer variables for a Space 
** object equal to another Space object. Used to link up rooms in the 
** castle.
**
** Parameters: A char value which represents the direction of the 
** pointer that will be set, and a pointer to Space which is the room
** that will be linked to that pointer. 
*********************************************************************/
void Space::setPointer(char dir, Space* loc)
{
	if (dir == 'R')
		this->right = loc;
	else if (dir == 'L')
		this->left = loc;
	else if (dir == 'U')
		this->up = loc;
	else if (dir == 'D')
		this->down = loc;
}

/*********************************************************************
** Function: Space::getInteger
**
** Description: Input validation function for integers.
**
** Parameters: A single string, which is the prompt that asks the user
** for a specific input.
**
** Return: Returns an integer which has been verified to be a
** non-negative and non-zero integer.
*********************************************************************/
int Space::getInteger(std::string prompt)
{
	int num;

	//run the desired prompt
	cout << prompt << endl;
	cin >> num;

	//if the number entered was not an integer, prompt the user to try again
	while (!cin)
	{
		cout << "Invalid choice. Please enter an integer value instead." << endl;
		cin.clear();  //clear the error flag on cin
		cin.ignore(); //skip to the next new line
		cin >> num;
	}

	return num;
}