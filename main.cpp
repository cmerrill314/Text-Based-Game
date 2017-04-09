/*********************************************************************
** Program Filename: game
** Author: Christopher Merrill
** Date: 12/4/2016
**
** Description: 
** CS162 Final Project. This program is a text based game
** entitled "Thief's Dilemma". The user navigates their way through a 
** castle, collecting items along the way that unlock new rooms and 
** eventually battling a dragon so that they can save the princess. A 
** virtual parent class "Space" manages the six rooms of the castle, and 
** the "Game" class manages the game logic and player stats. 
**
*********************************************************************/

#include "Game.hpp"
#include <iostream>
using namespace std;

int main()
{
	//notify user to play in full screen (for display purposes)
	cout << endl;
	cout << "Assure that you are in Full Screen mode" << endl << endl;

	//wait for the user to switch to full screen
	string temp;
	cout << "PRESS ENTER TO CONTINUE" << endl;
	getline(cin, temp);
	cin.clear();
	cout << "\033[2J\033[1;1H" << endl;

	//diplay the title image
	string imageLines = "";
	string fileName = "title.txt";

	ifstream inputFile;
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

	//opening story
	cout << "It is a dark and stormy night. You are a wandering thief, looking for a place to take refuge from" << endl;
	cout << "the downpour. Suddenly, you stumble upon what appears to be an old abandoned castle." << endl << endl;
	cout << "\"This could be a great opportunity to do some thieving!\" you think." << endl << endl;
	cout << "Little do you know that there's a whole lot more in store once you enter that door..." << endl << endl;

	//pause
	cout << "PRESS ENTER TO CONTINUE" << endl;
	getline(cin, temp);
	cin.clear();
	cout << "\033[2J\033[1;1H";
	
	//instantiate a game object and start the play loop
	Game castle;
	castle.play();

	return 0;
}