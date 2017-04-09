#include "Chambers.hpp"

/*********************************************************************
** Function: Chambers::menu
**
** Description: Displays the menu when the user enters the Chambers.
** A different menu is displayed depending on which actions the user
** has already taken in the game.
**
** Return: Returns a char value corresponding to the menu choice. This
** char value is used in the Game class play function to determine
** which action to take.
*********************************************************************/
char Chambers::menu()
{
	int choice;

	//if the lights are off and you don't have the MIRROR
	if (!lightsOn && !specItemObt)
	{
		cout << endl;
		cout << "What would you like to do?" << endl;
		cout << "1. Grab the shimmering object." << endl;
		cout << "2. Go back to the GRAND HALL." << endl;
		cout << "3. Manage Inventory." << endl;
		cout << "4. Quit Game." << endl;
		cout << endl;

		//input validation
		int choice = getInteger("Enter your choice:");

		while (choice <= 0 || choice > 4)
			choice = getInteger("Invalid choice. Enter a menu option instead:");

		cout << endl;

		if (choice == 1)
			return 'X';
		else if (choice == 2)
			return 'L';
		else if (choice == 3)
			return 'I';
		else
			return 'Q';
	}
	//if the lights are off
	else if (!lightsOn)
	{
		cout << endl;
		cout << "What would you like to do?" << endl;
		cout << "1. Illuminate room." << endl;
		cout << "2. Go back to the GRAND HALL." << endl;
		cout << "3. Manage Inventory." << endl;
		cout << "4. Quit Game." << endl;
		cout << endl;

		//input validation
		int choice = getInteger("Enter your choice:");

		while (choice <= 0 || choice > 4)
			choice = getInteger("Invalid choice. Enter a menu option instead:");

		cout << endl;

		if (choice == 1)
			return 'T';
		else if (choice == 2)
			return 'L';
		else if (choice == 3)
			return 'I';
		else
			return 'Q';
	}
	//if the lights are on
	else
	{
		cout << endl;
		cout << "What would you like to do?" << endl;
		cout << "1. Search room." << endl;
		cout << "2. Go back to the GRAND HALL." << endl;
		cout << "3. Manage Inventory." << endl;
		cout << "4. Quit Game." << endl;
		cout << endl;

		//input validation
		int choice = getInteger("Enter your choice:");

		while (choice <= 0 || choice > 4)
			choice = getInteger("Invalid choice. Enter a menu option instead:");

		cout << endl;

		if (choice == 1)
			return 'S';
		else if (choice == 2)
			return 'L';
		else if (choice == 3)
			return 'I';
		else
			return 'Q';
	}
}

/*********************************************************************
** Function: Chambers::displayTag
**
** Description: Displays the tagline that appears when a user enters
** the Chambers. The tagline is different depending on which actions
** the user has previously taken in the game.
*********************************************************************/
void Chambers::displayTag()
{
	//if the lights are off and you don't have the MIRROR
	if (!lightsOn && !specItemObt)
		cout << "It's dark, but a shimmering object glistens on the other end of the room" << endl << endl;
	//if the lights are off
	else if (!lightsOn)
		cout << "This room is too dark to search, who knows what could be in there?" << endl << endl;
	//if the lights are on
	else
		cout << "The King's most valuable personal items must be in here..." << endl << endl;
}

/*********************************************************************
** Function: Chambers::displayImage
**
** Description: Displays the Chambers room image. The image displayed
** is different depending on which actions the user has taken. The
** images are included in separate text files and have to be read into
** the program.
*********************************************************************/
void Chambers::displayImage()
{
	string imageLines = "";
	string fileName;

	ifstream inputFile;

	if (lightsOn)
		fileName = "chambers.txt";
	else
		fileName = "darkchambers.txt";

	inputFile.open(fileName.c_str());

	if (inputFile)
	{
		while (inputFile)
		{
			string temp;
			getline(inputFile, temp);
			temp += "\n";
			imageLines += temp;
		}
		cout << imageLines << endl;

		inputFile.close();
	}
	else
		cout << "ERROR: Image file wasn't found..." << endl;
}