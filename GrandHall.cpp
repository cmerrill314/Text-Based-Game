#include "GrandHall.hpp"

/*********************************************************************
** Function: GrandHall::menu
**
** Description: Displays the menu when the user enters the GrandHall.
**
** Return: Returns a char value corresponding to the menu choice. This
** char value is used in the Game class play function to determine
** which action to take.
*********************************************************************/
char GrandHall::menu()
{
	cout << "What would you like to do?" << endl;
	cout << "1. Examine the beam of light." << endl;
	cout << "2. Search room." << endl;
	cout << "3. Leave room." << endl;
	cout << "4. Manage Inventory." << endl;
	cout << "5. Quit Game." << endl;
	cout << endl;

	//input validation
	int choice = getInteger("Enter your choice:");

	while (choice <= 0 || choice > 5)
		choice = getInteger("Invalid choice. Enter a menu option instead:");

	cout << endl;

	if (choice == 1)
		return 'X';
	else if (choice == 2)
		return 'S';
	else if (choice == 3)
	{
		//exit room options:
		cout << "Where would you like to go?" << endl;
		cout << "1. Right to the KING'S CHAMBERS." << endl;
		cout << "2. Left to the LIBRARY." << endl;
		cout << "3. Down to the DUNGEON." << endl;
		cout << "4. Up to the TOWER." << endl;
		cout << endl;

		//input validation
		int choice = getInteger("Enter your choice:");

		while (choice <= 0 || choice > 4)
			choice = getInteger("Invalid choice. Enter a menu option instead:");

		cout << endl;

		if (choice == 1)
			return 'R';
		else if (choice == 2)
			return 'L';
		else if (choice == 3)
			return 'D';
		else
			return 'U';
	}
	else if (choice == 4)
		return 'I';
	else 
		return 'Q';
}

/*********************************************************************
** Function: GrandHall::displayTag
**
** Description: Displays the tagline that appears when a user enters
** the GrandHall. 
*********************************************************************/
void GrandHall::displayTag()
{
	cout << "A beam of light shines through an upper window onto the center of the floor..." << endl;
	cout << "You hear screams from the dungeon!" << endl << endl;
}

/*********************************************************************
** Function: Treasury::displayImage
**
** Description: Displays the Treasury room image. The images are 
** included in separate text files and have to be read into the program.
*********************************************************************/
void GrandHall::displayImage()
{
	string imageLines = "";
	
	ifstream inputFile;
	string fileName = "grandhall.txt";

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

