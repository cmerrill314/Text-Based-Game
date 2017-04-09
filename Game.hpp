/* Game.hpp is the Game class specification file.*/

#include "GrandHall.hpp"
#include "Chambers.hpp"
#include "Library.hpp"
#include "Treasury.hpp"
#include "Dungeon.hpp"
#include "Tower.hpp"
#include <cstdlib> 
#include <ctime>   
#include <list>

//include guard
#ifndef GAME_HPP 
#define GAME_HPP

class Game
{
private:
	//the castle's rooms:
	Space* grandHall;
	Space* chambers;
	Space* library;
	Space* treasury;
	Space* dungeon;
	Space* tower;

	//the thief's properties:
	Space* location;                    //thief's current location
	int health;                         //thief's current health
	std::list<std::string> inventory;   //thief's inventory
	std::list<std::string> discardPile; //thief's discarded items
	int MAX_INVENTORY;                  //thief's max inventory
	bool isDead;                        //whether or not the thief is dead
	bool gameWon;                       //whether or not the game has been won

	//time-related data members
	int waterLevel;

public:
	Game();

	void play();

	//special room functions
	void specialGrandHall();
	void specialChambers();
	void specialLibrary();
	void specialTreasury();
	void specialDungeon();
	void specialTower();

	//search room functions
	void searchGrandHall();
	void searchChambers();
	void searchLibrary();
	void searchTreasury();
	void searchTower();

	//inventory management functions:
	bool searchInventory(std::string);
	bool searchDiscardPile(std::string);
	void removeItem();

	//misc. funtions:
	void resetConsole();
	void pause();
	int getInteger(std::string);
	void winScreen();
	void loseScreen();
};

#endif