#include "Library.hpp"

/*********************************************************************
** Function: Library::menu
**
** Description: Displays the menu when the user enters the Library.
** A different menu is displayed depending on which actions the user
** has already taken in the game.
**
** Return: Returns a char value corresponding to the menu choice. This
** char value is used in the Game class play function to determine
** which action to take.
*********************************************************************/
char Library::menu()
{
	int choice;

	//if the lights are off
	if (!lightsOn)
	{
		cout << endl;
		cout << "What would you like to do?" << endl;
		cout << "1. Illuminate room." << endl;
		cout << "2. Go back to the GRAND HALL." << endl;
		cout << "3. Manage inventory." << endl;
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
			return 'R';
		else if (choice == 3)
			return 'I';
		else 
			return 'Q';
	}
	//if the treasury isn't unlocked and you have the ROYAL-JEWEL
	else if (!treasuryUnlocked && reqItemObt)
	{
		cout << endl;
		cout << "What would you like to do?" << endl;
		cout << "1. Place the ROYAL-JEWEL in the gargoyle's eye socket." << endl;
		cout << "2. Search the room." << endl;
		cout << "3. Go back to the GRAND HALL." << endl;
		cout << "4. Manage inventory." << endl;
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
			return 'R';
		else if (choice == 4)
			return 'I';
		else
			return 'Q';
	}
	//if the tresury is locked
	else if (!treasuryUnlocked)
	{
		cout << endl;
		cout << "What would you like to do?" << endl;
		cout << "1. Examine Sword." << endl;
		cout << "2. Search the room." << endl;
		cout << "3. Go back to the GRAND HALL." << endl;
		cout << "4. Manage inventory." << endl;
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
			return 'R';
		else if (choice == 4)
			return 'I';
		else
			return 'Q';
	}
	//if the treasury is unlocked, but you don't have the HERO'S-SWORD
	else if (!specItemObt)
	{
		cout << endl;
		cout << "What would you like to do?" << endl;
		cout << "1. Examine Sword." << endl;
		cout << "2. Search the room." << endl;
		cout << "3. Leave room." << endl;
		cout << "4. Manage inventory." << endl;
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
			cout << endl;
			cout << "Where would you like to go?" << endl;
			cout << "1. Right to the GRAND HALL." << endl;
			cout << "2. Down to the HIDDEN TREASURY." << endl;
			cout << endl;

			//input validation
			int choice = getInteger("Enter your choice:");

			while (choice <= 0 || choice > 2)
				choice = getInteger("Invalid choice. Enter a menu option instead:");

			cout << endl;

			if (choice == 1)
				return 'R';
			else if (choice == 2)
				return 'D';
		}
		else if (choice == 4)
			return 'I';
		else
			return 'Q';
	}
	//if you have the HERO'S SWORD
	else
	{
		cout << endl;
		cout << "What would you like to do?" << endl;
		cout << "1. Search room." << endl;
		cout << "2. Leave room." << endl;
		cout << "3. Manage inventory." << endl;
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
		{
			//exit room options
			cout << endl;
			cout << "Where would you like to go?" << endl;
			cout << "1. Right to the GRAND HALL." << endl;
			cout << "2. Down to the HIDDEN TREASURY." << endl;
			cout << endl;

			//input validation
			int choice = getInteger("Enter your choice:");

			while (choice <= 0 || choice > 2)
				choice = getInteger("Invalid choice. Enter a menu option instead:");

			cout << endl;

			if (choice == 1)
				return 'R';
			else if (choice == 2)
				return 'D';
		}
		else if (choice == 4)
			return 'I';
		else
			return 'Q';
		
	}
}

/*********************************************************************
** Function: Library::displayTag
**
** Description: Displays the tagline that appears when a user enters
** the Library. The tagline is different depending on which actions
** the user has previously taken in the game.
*********************************************************************/
void Library::displayTag()
{
	//if the lights are off
	if (!lightsOn)
		cout << "It's too dark to enter..." << endl << endl;
	//if the treasury isn't unlocked and you have the ROYAL-JEWEL
	else if (!treasuryUnlocked && reqItemObt)
		cout << "You notice a small gargoyle near a bookshelf that is missing an eye..." << endl;
	//if the treasury is unlocked, but you don't have the HERO'S-SWORD
	else if (!treasuryUnlocked || !specItemObt)
		cout << "There is a sword on the mantlepiece!" << endl << endl;
	//if you have the HERO'S SWORD
	else
		cout << "All you see are books, there's no value in books..." << endl << endl;
}

/*********************************************************************
** Function: Library::displayImage
**
** Description: Displays the Library room image. The image displayed
** is different depending on which actions the user has taken. The
** images are included in separate text files and have to be read into
** the program.
*********************************************************************/
void Library::displayImage()
{
	string imageLines = "";
	string fileName;

	ifstream inputFile;

	if (lightsOn)
	{
		if (!treasuryUnlocked)
			fileName = "library1.txt";
		else if (!specItemObt)
			fileName = "library2.txt";
		else
			fileName = "library3.txt";
	}
	else
		fileName = "darklibrary.txt";

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