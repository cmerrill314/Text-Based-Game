#include "Dungeon.hpp"

/*********************************************************************
** Function: Dungeon::menu
**
** Description: Displays the menu when the user enters the Dungeon.
** A different menu is displayed depending on which actions the user
** has already taken in the game.
**
** Return: Returns a char value corresponding to the menu choice. This
** char value is used in the Game class play function to determine
** which action to take.
*********************************************************************/
char Dungeon::menu()
{
	int choice;

	//if the lights are off
	if (!lightsOn)
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
			return 'U';
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
		cout << "1. Talk to the PRINCESS." << endl;
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
			return 'U';
		else if (choice == 3)
			return 'I';
		else
			return 'Q';
	}
}

/*********************************************************************
** Function: Dungeon::displayTag
**
** Description: Displays the tagline that appears when a user enters
** the Dungeon. The tagline is different depending on which actions
** the user has previously taken in the game.
*********************************************************************/
void Dungeon::displayTag()
{
	//if the lights are off and you don't have a LIT-TORCH
	if (!lightsOn && !reqItemObt)
	{
		cout << "It's too dark to enter. You hear running water and the voice of the princess:" << endl;
		cout << "PRINCESS: Please, you have to help. Come back when you have a LIT-TORCH!" << endl;
	}
	//if the lights are off and you have a LIT-TORCH
	else if (!lightsOn)
	{
		cout << "It's dark and scary in here. You here running water and the voice of the princess:" << endl;
		cout << "PRINCESS: Quick, use your LIT-TORCH to illuminate the room" << endl;
	}
	//if the lights are on
	else
		cout << "You see the princess locked behind steel bars..." << endl;
}

/*********************************************************************
** Function: Dungeon::displayImage
**
** Description: Displays the Dungeon room image. The image displayed
** is different depending on which actions the user has taken. The
** images are included in separate text files and have to be read into
** the program.
*********************************************************************/
void Dungeon::displayImage()
{
	string imageLines = "";
	string fileName;

	ifstream inputFile;

	if (lightsOn)
		fileName = "dungeon.txt";
	else
		fileName = "darkdungeon.txt";

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