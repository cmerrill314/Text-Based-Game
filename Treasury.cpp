#include "Treasury.hpp"

/*********************************************************************
** Function: Treasury::menu
**
** Description: Displays the menu when the user enters the Treasury. 
** A different menu is displayed depending on which actions the user 
** has already taken in the game. 
**
** Return: Returns a char value corresponding to the menu choice. This
** char value is used in the Game class play function to determine 
** which action to take. 
*********************************************************************/
char Treasury::menu()
{
	//if the lights are off
	if (!lightsOn)
	{
		cout << endl;
		cout << "What would you like to do?" << endl;
		cout << "1. Illuminate room." << endl;
		cout << "2. Go back to the LIBRARY." << endl;
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
			return 'U';
		else if (choice == 3)
			return 'I';
		else
			return 'Q';
	}
	//if the lights are on, but the chest isn't open
	else if (!specItemObt)
	{
		cout << endl;
		cout << "What would you like to do?" << endl;
		cout << "1. Examine chest." << endl;
		cout << "2. Search room." << endl;
		cout << "3. Go back to the LIBRARY." << endl;
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
			return 'U';
		else if (choice == 4)
			return 'I';
		else
			return 'Q';
	}
	//if the lights are on and the chest has been opened
	else
	{
		cout << endl;
		cout << "What would you like to do?" << endl;
		cout << "1. Search room." << endl;
		cout << "2. Go back to the LIBRARY." << endl;
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
			return 'U';
		else if (choice == 3)
			return 'I';
		else
			return 'Q';
	}
}

/*********************************************************************
** Function: Treasury::displayTag
**
** Description: Displays the tagline that appears when a user enters 
** the Treasury. The tagline is different depending on which actions 
** the user has previously taken in the game. 
*********************************************************************/
void Treasury::displayTag()
{
	//if the lights are off
	if (!lightsOn)
		cout << "It's too dark to enter" << endl;
	//if the lights are on and the chest hasn't been opened
	else if (!specItemObt)
	{
		cout << "You are surrounded by mountains of gold and jewels! ";
		cout << "A grand chest sits against the far wall" << endl;
	}
	//if the lights are on and the chest has been opened
	else
		cout << "You are surrounded by mountains of gold and jewels!";

}

/*********************************************************************
** Function: Treasury::displayImage
**
** Description: Displays the Treasury room image. The image displayed
** is different depending on which actions the user has taken. The 
** images are included in separate text files and have to be read into
** the program. 
*********************************************************************/
void Treasury::displayImage()
{
	string imageLines = "";
	string fileName;

	ifstream inputFile;

	//determine which image to display
	if (!lightsOn)
		fileName = "darktreasury.txt";
	else
		fileName = "treasury.txt";

	//open the input file
	inputFile.open(fileName.c_str());

	//read in the image
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

		//close the file
		inputFile.close();
	}
	else
		cout << "ERROR: Image file wasn't found..." << endl;
}