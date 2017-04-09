#include "Tower.hpp"

/*********************************************************************
** Function: Tower::menu
**
** Description: Displays the menu when the user enters the Tower.
** A different menu is displayed depending on which actions the user
** has already taken in the game.
**
** Return: Returns a char value corresponding to the menu choice. This
** char value is used in the Game class play function to determine
** which action to take.
*********************************************************************/
char Tower::menu()
{
	//if the dragon has been defeated
	if (specItemObt)
	{
		cout << "What would you like to do?" << endl;
		cout << "1. Search room." << endl;
		cout << "2. Go down to the GRAND HALL." << endl;
		cout << "3. Manage inventory." << endl;
		cout << "4. Quit Game." << endl;
		cout << endl;

		//input validation
		int choice = getInteger("Enter your choice:");

		while (choice <= 0 || choice > 4)
			choice = getInteger("Invalid choice. Enter a menu option instead:");

		cout << endl;

		//return corresponding result
		if (choice == 1)
			return 'S';
		else if (choice == 2)
			return 'D';
		else if (choice == 3)
			return 'I';
		else
			return 'Q';
	}
	//if the dragon has not been defeated
	else
	{
		cout << "What would you like to do?" << endl;
		cout << "1. Fight Dragon." << endl;
		cout << "2. Screw the dragon, run back to the GRAND HALL." << endl;
		cout << "3. Manage inventory." << endl;
		cout << "4. Quit Game." << endl;
		cout << endl;

		//input validation
		int choice = getInteger("Enter your choice:");

		while (choice <= 0 || choice > 4)
			choice = getInteger("Invalid choice. Enter a menu option instead:");

		cout << endl;

		//return corresponding result
		if (choice == 1)
			return 'X';
		else if (choice == 2)
			return 'D';
		else if (choice == 3)
			return 'I';
		else
			return 'Q';
	}
}

/*********************************************************************
** Function: Tower::displayTag
**
** Description: Displays the tagline that appears when a user enters
** the Tower. The tagline is different depending on which actions
** the user has previously taken in the game.
*********************************************************************/
void Tower::displayTag()
{
	//if the dragon has been defeated
	if (specItemObt)
		cout << "The remains of the dragon lie on the floor..." << endl << endl;
	//if the dragon has not been defeated
	else
		cout << "A vicious dragon roars and begins to charge!" << endl << endl;
}

/*********************************************************************
** Function: Tower::displayImage
**
** Description: Displays the Tower room image. The image displayed
** is different depending on which actions the user has taken. The
** images are included in separate text files and have to be read into
** the program.
*********************************************************************/
void Tower::displayImage()
{
	string imageLines = "";
	string fileName;

	ifstream inputFile;

	if (!specItemObt)
		fileName = "tower1.txt";
	else
		fileName = "tower2.txt";

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