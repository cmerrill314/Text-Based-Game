#include "Game.hpp"

/*********************************************************************
** Function: Game::Game
**
** Description: Game class constructor. Creates the six spaces within 
** the castle, links the spaces using the setPointer function in the 
** Space class, and initializes the theif's starting stats.
*********************************************************************/
Game::Game()
{
	//create Spaces
	grandHall = new GrandHall("GRAND HALL");
	chambers = new Chambers("KING'S CHAMBERS");
	library = new Library("LIBRARY");
	treasury = new Treasury("HIDDEN TREASURY");
	dungeon = new Dungeon("DUNGEON");
	tower = new Tower("TOWER");

	//link Spaces
	grandHall->setPointer('R', chambers);
	grandHall->setPointer('L', library);
	grandHall->setPointer('U', tower);
	grandHall->setPointer('D', dungeon);
	chambers->setPointer('L', grandHall);
	library->setPointer('R', grandHall);
	library->setPointer('D', treasury);
	treasury->setPointer('U', library);
	dungeon->setPointer('U', grandHall);
	tower->setPointer('D', grandHall);

	//initialize the thief's parameters
	health = 100;
	inventory.push_front("UNLIT-TORCH");
	location = grandHall;
	MAX_INVENTORY = 6;
	isDead = false;
	gameWon = false;
	waterLevel = 0;

	//seed the random number generator
	srand(time(0));
}

/*********************************************************************
** Function: Game::play
**
** Description: The main play loop for the entire game. Displays a 
** rooms image and allows the player to "enter" a room. Once inside a
** room, the player will have multiple menu options. Whichever option
** the player selects will return a char value to the play loop:
**
** R = move to the room to the right
** L = move to the room to the left
** U = move up to the next room
** D = move down to the next room
** X = run the room's "special" function
** S = run the room's "search" function
** I = manage inventory
** T = use torch
** Q = quit game
**
** The play loop will continue until one of the following things 
** happens: The player decides to quit the game, the player dies, the 
** princess drowns, or the player beats the game.
*********************************************************************/
void Game::play()
{
	char value;

	do
	{
		resetConsole();

		//display room tag line
		location->displayTag();

		//run the room menu
		value = location->menu();

		if (value == 'R')
		{
			//move right to the next room
			location = location->getRight();
		}
		else if (value == 'L')
		{
			//move left to the next room
			location = location->getLeft();
		}
		else if (value == 'U')
		{
			//move upto the next room
			location = location->getUp();
		}
		else if (value == 'D')
		{
			//move down to the next room
			location = location->getDown();
		}
		else if (value == 'X')
		{
			//run the room's Special function
			if (location == grandHall)
				specialGrandHall();
			else if (location == chambers)
				specialChambers();
			else if (location == library)
				specialLibrary();
			else if (location == treasury)
				specialTreasury();
			else if (location == dungeon)
				specialDungeon();
			else if (location == tower)
				specialTower();
		}
		else if (value == 'S')
		{
			//run the room's Search function
			if (location == grandHall)
				searchGrandHall();
			else if (location == chambers)
				searchChambers();
			else if (location == library)
				searchLibrary();
			else if (location == treasury)
				searchTreasury();
			else if (location == tower)
				searchTower();
		}
		else if (value == 'I')
		{
			//manage the players inventory
			removeItem();
		}
		else if (value == 'T')
		{
			//if you have a LIT-TORCH, turn the lights on
			if (searchInventory("LIT-TORCH"))
			{
				resetConsole();
				cout << "You use your LIT-TORCH to light the candle holders in the ";
				cout << location->getName() << "." << endl << endl;

				//set the room's lightsOn to true
				location->setLightsOn(true);
				pause();
			}
			//if you don't have a LIT-TORCH, notify the user 
			else
			{
				resetConsole();
				cout << "You have no way to illuminate the room. ";
				cout << "If only you had a LIT-TORCH..." << endl << endl;
				pause();
			}
		}

		//check if the player has died
		if (isDead)
		{
			resetConsole();
			cout << "You have died..." << endl;
			pause();
		}

		//increment the water level in the dungeon
		waterLevel++;

		//check the time
		if (waterLevel == 15)
		{
			resetConsole();
			cout << "You hear the PRINCESS shout out from the dungeon:" << endl << endl;
			cout << "PRINCESS: Please hurry! The water is up to my knees now!" << endl << endl;
			pause();
		}
		else if (waterLevel == 30)
		{
			resetConsole();
			cout << "You hear the PRINCESS shout out from the dungeon:" << endl << endl;
			cout << "PRINCESS: Please hurry! The water is almost to my head!" << endl << endl;
			pause();
		}
		else if (waterLevel == 45)
		{
			resetConsole();
			cout << "You took to long...the PRINCESS has drowned..." << endl << endl;
			isDead = true;
			pause();
		}

	} while (value != 'Q' && !isDead && !gameWon);

	//display the win or lose screen depending on the outcome
	if (gameWon)
		winScreen();
	else
		loseScreen();

	//deallocate memory
	delete grandHall;
	delete chambers;
	delete library;
	delete treasury;
	delete dungeon;
	delete tower;
}

/*********************************************************************
** Function: Game::specialGrandHall
**
** Description: The special function for the Library room. Allows the
** user to lite their UNLIT-TORCH, provided they have the obtained the
** MIRROR first. 
*********************************************************************/
void Game::specialGrandHall()
{
	//if you have already lit your torch, notify the user
	if (searchInventory("LIT-TORCH"))
	{
		resetConsole();
		cout << "Your torch is already lit..." << endl << endl;
		pause();
	}
	//otherwise, if you have the MIRROR, light your torch with the beam of light
	else
	{
		if (searchInventory("MIRROR") && searchInventory("UNLIT-TORCH"))
		{
			resetConsole();
			cout << "You reflect the beam of light off of the MIRROR to light your torch." << endl;
			cout << "ITEM OBTAINED: LIT-TORCH" << endl << endl;

			inventory.remove("UNLIT-TORCH");
			inventory.push_back("LIT-TORCH");

			grandHall->setSpecItemObt(true);
			dungeon->setReqItemObt(true);

			pause();
		}
		else
		{
			resetConsole();
			cout << "The beam of light is strong, maybe you can reflect it off of something?" << endl << endl;
			pause();
		}
	}
}

/*********************************************************************
** Function: Game::specialChambers
**
** Description: The special function for the Library room. Allows the 
** user to obtain the MIRROR, provided they have enough room in their 
** inventory. 
*********************************************************************/
void Game::specialChambers()
{
	//if your inventory is full, notify the user
	if (inventory.size() == MAX_INVENTORY)
	{
		resetConsole();
		cout << "Unable to grab the object, you're already carrying too much..." << endl;
		cout << "Manage your inventory first." << endl << endl;
		pause();
	}
	//otherwise grab the MIRROR
	else
	{
		resetConsole();
		cout << "You run into the room, grab the object, and run back out." << endl;
		cout << "ITEM OBTAINED: MIRROR" << endl << endl;

		inventory.push_back("MIRROR");

		chambers->setSpecItemObt(true);
		grandHall->setReqItemObt(true);
		pause();
	}
}

/*********************************************************************
** Function: Game::specialLibrary
**
** Description: The special function for the Library room. There are
** two "special" actions that can occur in the Library. The first 
** allows the user to unlock the HIDDEN TREASURY, and the second allows
** the user to unlock the HERO'S-SWORD. In order to unlock the treasury,
** the player must have obtained the ROYAL-JEWEL from the PRINCESS. In
** order to unlock the HERO'S SWORD, the user must have obtained the
** GOLDEN SHIELD from the treasury. 
*********************************************************************/
void Game::specialLibrary()
{
	//if you have the ROYAL-JEWEL, unlock the HIDDEN TREASURY
	if (!location->getTreasuryUnlocked() && searchInventory("ROYAL-JEWEL"))
	{
		resetConsole();
		cout << "You place the ROYAL-JEWEL in the gargoyle's empty eye socket..." << endl;
		cout << "The bookcase opens up to reveal a hidden stairway, you walk down." << endl << endl;

		library->setTreasuryUnlocked(true);
		location = location->getDown();

		inventory.remove("ROYAL-JEWEL");
		pause();
	}
	//if you've unlocked the treasury, but don't have the GOLDEN-SHIELD
	else if (!location->getTreasuryUnlocked() || !searchInventory("GOLDEN-SHIELD"))
	{
		resetConsole();
		cout << "The sword is incased in thick glass, you're going to need something heavy to smash it..." << endl << endl;
		pause();
	}
	//if you have the GOLDEN-SHIELD, and you have room for a new item, bash the glass casing and retrieve the HERO'S-SWORD
	else
	{
		if (inventory.size() == MAX_INVENTORY)
		{
			resetConsole();
			cout << "You could probably use the GOLDEN-SHIELD to bash the glass, but your inventory is full..." << endl;
			cout << "Manage your inventory first." << endl << endl;
			pause();
		}
		else
		{
			resetConsole();
			cout << "You use the GOLDEN-SHIELD to bash through the glass." << endl << endl;
			cout << "ITEM OBTAINED: HERO'S-SWORD" << endl << endl;

			inventory.push_back("HERO'S-SWORD");

			library->setSpecItemObt(true);
			pause();
		}
	}
}

/*********************************************************************
** Function: Game::specialTreasury
**
** Description: The special function for the Treasury room. Allows the
** player to open the chest containing the GOLDEN-SHIELD, provided they
** have room in their inventory. 
*********************************************************************/
void Game::specialTreasury()
{
	//if your inventory is full, notify the user
	if (inventory.size() == MAX_INVENTORY)
	{
		resetConsole();
		cout << "You open the chest which reveals a magnificent GOLDEN-SHIELD, but your inventory is full..." << endl;
		cout << "Manage your inventory first." << endl << endl;
		pause();
	}
	//if you have room, obtain the GOLDEN-SHIELD from the chest
	else
	{
		resetConsole();
		cout << "You open the chest, revealing a magnificent GOLDEN-SHIELD!" << endl;
		cout << "This should protect you from the dragon's flames." << endl << endl;
		cout << "ITEM OBTAINED: GOLDEN-SHIELD" << endl << endl;

		inventory.push_back("GOLDEN-SHIELD");

		treasury->setSpecItemObt(true);
		pause();
	}
}

/*********************************************************************
** Function: Game::specialDungeon
**
** Description: The special function for the Dungeon room, which is 
** the ability to talk to the PRINCESS to gain insight on your progress
** in the game. Depending on which items you have obtained, the 
** PRINCESS will provide different information. 
*********************************************************************/
void Game::specialDungeon()
{
	//if you have the dungeon key, free the PRINCESS
	if (searchInventory("DUNGEON-KEY"))
	{
		resetConsole();
		cout << "PRINCESS: Oh thank goodness, you've found the DUNGEON KEY. Quick, set me free!" << endl << endl;
		cout << "You free the PRINCESS..." << endl << endl;
		gameWon = true;
		pause();
	}
	//if you don't have the ROYAL-JEWEL yet, listen to the story
	else if (!dungeon->getSpecItemObt())
	{
		resetConsole();
		cout << "PRINCESS: Please, you have to help me. The storm is so bad that the DUNGEON is flooding..." << endl;
		cout << "          I don't have much time, you have to get the DUNGEON KEY to unlock my chains. The key lies" << endl;
		cout << "          up in the TOWER. You'll have to slay the dragon and remove the DUNGEON KEY from its stomach," << endl;
		cout << "          but to do so you'll need to be properly equipped. There exists a secret room within" << endl;
		cout << "          the LIBRARY, you can access it if you take this..." << endl << endl;

		if (inventory.size() == MAX_INVENTORY)
		{
			cout << "          ...you don't have room to take this...have you been stealing...nevermind! Manage" << endl;
			cout << "          your inventory and come back when you have room!" << endl << endl;
			pause();
		}
		else
		{
			inventory.push_back("ROYAL-JEWEL");

			cout << "ITEM OBTAINED: ROYAL-JEWEL" << endl << endl;

			dungeon->setSpecItemObt(true);
			library->setReqItemObt(true);

			cout << "PRINCESS: Inside the secret room is an item that can protect you from the dragon's fire." << endl;
			cout << "          Now please hurry, slay the dragon and return with the DUNGEON KEY!" << endl << endl;
			pause();
		}
	}
	//if you have the HERO'S-SWORD and GOLDEN-SHIELD
	else if (searchInventory("HERO'S-SWORD") && ("GOLDEN-SHIELD"))
	{
		resetConsole();
		cout << "PRINCESS: You have the GOLDEN-SHIELD and a weapon, what are you waiting for? Go slay" << endl;
		cout << "          that dragon!" << endl << endl;
		pause();
	}
	//if you only have the GOLDEN-SHIELD
	else if (searchInventory("GOLDEN-SHIELD"))
	{
		resetConsole();
		cout << "PRINCESS: Great you found the GOLDEN-SHIELD. Now take whatever weapon you can find" << endl;
		cout << "          and go defeat the dragon! Quick!" << endl << endl;
		pause();
	}
	//if you've already taken the ROYAL-JEWEL, but don't have a shield or sword yet
	else if (!searchInventory("HERO'S-SWORD") && !searchInventory("GOLDEN-SHIELD"))
	{
		resetConsole();
		cout << "PRINCESS: Hurry, you have to retrieve the item from the LIBRARY secret room. Its the" << endl;
		cout << "          only way to protect yourself from the dragon's fire..." << endl << endl;
		pause();
	}
}

/*********************************************************************
** Function: Game::specialTower
**
** Description: The special function for the Tower room. Runs 
** the logic for the final battle against the dragon. 
*********************************************************************/
void Game::specialTower()
{
	bool dragonDead = false;
	int dragonHealth = 100;
	int attack;
	int defense;
	int choice;

	do
	{
		resetConsole();

		//calculate attack/defense values
		attack = rand() % 4 + 1;
		defense = rand() % 3 + 1;

		//display dragon's health
		cout << "DRAGON'S HEALTH: " << dragonHealth << endl << endl;

		//initiate fight sequence
		cout << "The dragon blows fire at you" << endl;
		if (searchInventory("GOLDEN-SHIELD"))
		{
			if (defense == 1)
			{
				cout << "You raise the GOLDEN-SHIELD a little too late, and are burned." << endl;
				health -= 15;
			}
			else if (defense == 2)
			{
				cout << "You block most of the flames with the GOLDEN-SHIELD" << endl;
				health -= 5;
			}
			else
				cout << "You are completely protected by the GOLDEN-SHIELD" << endl;
		}
		else
		{
			cout << "You have no protection! You are badly burned..." << endl;
			health -= 25;
		}
		
		if (searchInventory("HERO'S-SWORD"))
		{
			if (attack == 1)
			{
				cout << "You attempt to strike, but miss..." << endl << endl;
			}
			else if (attack == 2)
			{
				cout << "You barely clip the dragon with the HERO'S-SWORD" << endl << endl;
				dragonHealth -= 15;
			}
			else if (attack == 3)
			{
				cout << "You strike the dragon with the HERO'S-SWORD" << endl << endl;
				dragonHealth -= 25;
			}
			else
			{
				cout << "You deliver a devistating blow to the dragon with the HERO'S-SWORD!" << endl << endl;
				dragonHealth -= 50;
			}
		}
		else
			cout << "You have no weapon, you can't fight back!" << endl << endl;


		//check to see if the user or the dragon is dead
		if (dragonHealth <= 0 || health <= 0)
		{
			if (dragonHealth <= 0)
				dragonDead = true;

			if (health <= 0)
				isDead = true;

			pause();
			resetConsole();
		}
		else
		{
			//if the user has a health potion, ask if they want to use it
			if (searchInventory("HEALTH-POTION"))
			{
				pause();
				resetConsole();

				cout << "You have a health potion, do you want to use it?" << endl;
				cout << "1. Use it." << endl;
				cout << "2. Save it." << endl;
				cout << endl;

				//input validation
				choice = getInteger("Enter your choice:");

				while (choice <= 0 || choice > 2)
					choice = getInteger("Invalid choice. Enter a menu option instead:");

				cout << endl;

				if (choice == 1)
				{
					cout << "You drink the health potion...you feel like a whole new thief!" << endl << endl;
					health += 30;
				}
			}

			pause();
			resetConsole();

			//ask the user if they want to fight or run
			cout << "What would you like to do?" << endl;
			cout << "1. Keep fighting." << endl;
			cout << "2. Run for your life." << endl;
			cout << endl;

			//input validation
			choice = getInteger("Enter your choice:");

			while (choice <= 0 || choice > 2)
				choice = getInteger("Invalid choice. Enter a menu option instead:");

			cout << endl;
		}

	} while (!dragonDead && !isDead && choice != 2);

	if (dragonDead)
	{
		cout << "YOU HAVE DEFEATED THE DRAGON!!!" << endl << endl;
		cout << "You slice into its stomach to retrieve the DUNGEON-KEY" << endl << endl;

		tower->setSpecItemObt(true);

		//verify inventory has space
		if (inventory.size() == MAX_INVENTORY)
			cout << "But you have no room to pick it up, manage your inventory first!" << endl << endl;
		else
		{
			inventory.push_back("DUNGEON-KEY");
			cout << "ITEM OBTAINED: DUNGEON-KEY" << endl << endl;
			cout << "Quick, we have to get to the PRINCESS before she drowns!" << endl << endl;
		}

		pause();
		resetConsole();
	}
}

/*********************************************************************
** Function: Game::searchGrandHall
**
** Description: The search function for the Grand Hall room. The user
** decides where they would like to search. Some options contain items
** and other options contain dangers.
*********************************************************************/
void Game::searchGrandHall()
{
	int choice;

	do
	{
		resetConsole();

		cout << "What would you like to search?" << endl;
		cout << "1. Check under the rug." << endl;
		cout << "2. Check the cabinet." << endl;
		cout << "3. Check the crest on the wall." << endl;
		cout << "4. Back to room menu." << endl;
		cout << endl;

		//input validation
		choice = getInteger("Enter your choice:");

		while (choice <= 0 || choice > 4)
			choice = getInteger("Invalid choice. Enter a menu option instead:");

		cout << endl;

		if (choice == 1)
		{
			resetConsole();
			cout << "You check under the rug..." << endl;

			//if you haven't already recieved the item
			if (!searchDiscardPile("KING'S-LETTER") && !searchInventory("KING'S-LETTER"))
			{
				cout << "You find a letter!" << endl << endl;

				//verify inventory has space
				if (inventory.size() == MAX_INVENTORY)
				{
					cout << "But you have no room to pick it up, manage your inventory first!" << endl;
					pause();
				}
				else
				{
					//display KING'S-LETTER
					cout << "It reads:" << endl << endl;
					cout << "To whatever brave and honorable soul has entered my castle," << endl << endl;
					cout << "I have been kidnapped by an evil Wizard. He has locked my daughter away" << endl;
					cout << "in the dungeon and fed the key to a wicked beast in the tower. Please" << endl;
					cout << "save my daughter before it is too late! I will be forever in your debt..." << endl << endl;
					cout << "Sincerely," << endl << "The King" << endl << endl;

					//add KING'S-LETTER to inventory
					inventory.push_back("KING'S-LETTER");
					cout << "ITEM OBTAINED: KING'S-LETTER" << endl << endl;

					pause();
				}
			}
			else
			{
				cout << "You've already looked here!" << endl << endl;
				pause();
			}
				
		}
		else if (choice == 2)
		{
			resetConsole();
			cout << "You search the cabinet..." << endl;

			//if you haven't already recieved the item
			if (!searchDiscardPile("SILVER-TIARA") && !searchInventory("SILVER-TIARA"))
			{
				cout << "You find a SILVER-TIARA" << endl << endl;

				//verify inventory has space
				if (inventory.size() == MAX_INVENTORY)
				{
					cout << "But you have no room to pick it up, manage your inventory first!" << endl;
					pause();
				}
				else
				{
					//add SILVER-TIARA to inventory
					inventory.push_back("SILVER-TIARA");
					cout << "ITEM OBTAINED: SILVER-TIARA" << endl << endl;

					pause();
				}
			}
			else
			{
				cout << "You've already looked here!" << endl << endl;
				pause();
			}
		}
		else if (choice == 3)
		{
			resetConsole();
			cout << "You check the crest on the wall..." << endl;
			cout << "It's solid gold, in the shape of the royal symbol! But its too big to grab..." << endl << endl;
			pause();
		}
		else if (choice != 4)
			cout << "Invalid choice. Enter a menu option instead:" << endl;

	} while (choice != 4);
}

/*********************************************************************
** Function: Game::searchChambers
**
** Description: The search function for the Chambers room. The user
** decides where they would like to search. Some options contain items
** and other options contain dangers.
*********************************************************************/
void Game::searchChambers()
{
	int choice;

	do
	{
		resetConsole();

		cout << "What would you like to search?" << endl;
		cout << "1. Check under the bed." << endl;
		cout << "2. Check the wardrobe." << endl;
		cout << "3. Check the dresser drawers." << endl;
		cout << "4. Back to room menu." << endl;
		cout << endl;

		//input validation
		choice = getInteger("Enter your choice:");

		while (choice <= 0 || choice > 4)
			choice = getInteger("Invalid choice. Enter a menu option instead:");

		cout << endl;

		if (choice == 1)
		{
			resetConsole();
			cout << "You check under the bed..." << endl;
			cout << "A black cat hisses and scratches you in the face!" << endl << endl;
			health -= 10;

			//if the cat kills you, end the game
			if (health <= 0)
			{
				isDead = true;
				choice = 4;
			}
			
			pause();
		}
		else if (choice == 2)
		{
			resetConsole();
			cout << "You search the wardrobe..." << endl;

			//if you haven't already recieved the item
			if (!searchDiscardPile("KING'S-ROBES") && !searchInventory("KING'S-ROBES"))
			{
				cout << "You find the KING'S-ROBES!" << endl << endl;

				//verify inventory has space
				if (inventory.size() == MAX_INVENTORY)
				{
					cout << "But you have no room to pick them up, manage your inventory first!" << endl;
					pause();
				}
				else
				{
					//add KING'S-ROBES to inventory
					inventory.push_back("KING'S-ROBES");
					cout << "All of the other thieves will be so jealous when you show up in these..." << endl << endl;
					cout << "ITEM OBTAINED: KING'S-ROBES" << endl << endl;
					pause();
				}
			}
			else
			{
				cout << "You've already looked here!" << endl << endl;
				pause();
			}
		}
		else if (choice == 3)
		{
			resetConsole();
			cout << "You search the dresser drawers..." << endl;

			//if you haven't already recieved the item
			if (!chambers->getHealthPotionFound())
			{
				cout << "You find a HEALTH-POTION!" << endl << endl;

				//verify inventory has space
				if (inventory.size() == MAX_INVENTORY)
				{
					cout << "But you have no room to pick it up, manage your inventory first!" << endl;
					pause();
				}
				else
				{
					//add KING'S-ROBES to inventory
					inventory.push_back("HEALTH-POTION");
					cout << "ITEM OBTAINED: HEALTH-POTION" << endl << endl;
					chambers->setHealthPotionFound(true);
					pause();
				}
			}
			else
			{
				cout << "You've already looked here!" << endl << endl;
				pause();
			}
		}
		else if (choice != 4)
			cout << "Invalid choice. Enter a menu option instead:" << endl;

	} while (choice != 4);
}

/*********************************************************************
** Function: Game::searchLibrary
**
** Description: The search function for the Library room. The user
** decides where they would like to search. Some options contain items
** and other options contain dangers.
*********************************************************************/
void Game::searchLibrary()
{
	int choice;

	do
	{
		resetConsole();

		cout << "What would you like to search?" << endl;
		cout << "1. Check the bookshelf." << endl;
		cout << "2. Check under the rug." << endl;
		cout << "3. Check the fireplace." << endl;
		cout << "4. Back to room menu." << endl;
		cout << endl;

		//input validation
		choice = getInteger("Enter your choice:");

		while (choice <= 0 || choice > 4)
			choice = getInteger("Invalid choice. Enter a menu option instead:");

		cout << endl;

		if (choice == 1)
		{
			resetConsole();
			cout << "You search the bookshelf..." << endl;

			//if you haven't already recieved the item
			if (!searchDiscardPile("GOLD-FIGURINE") && !searchInventory("GOLD-FIGURINE"))
			{
				cout << "You find a GOLD-FIGURINE!" << endl << endl;

				//verify inventory has space
				if (inventory.size() == MAX_INVENTORY)
				{
					cout << "But you have no room to pick it up, manage your inventory first!" << endl;
					pause();
				}
				else
				{
					//add KING'S-ROBES to inventory
					inventory.push_back("GOLD-FIGURINE");
					cout << "ITEM OBTAINED: GOLD-FIGURINE" << endl << endl;
					pause();
				}
			}
			else
			{
				cout << "You've already looked here!" << endl << endl;
				pause();
			}
		}
		else if (choice == 2)
		{
			resetConsole();
			cout << "You search under the rug..." << endl;

			//if you haven't already recieved the item
			if (!library->getHealthPotionFound())
			{
				cout << "There's a secret compartment. You find a HEALTH-POTION!" << endl << endl;

				//verify inventory has space
				if (inventory.size() == MAX_INVENTORY)
				{
					cout << "But you have no room to pick it up, manage your inventory first!" << endl;
					pause();
				}
				else
				{
					//add HEALTH-POTION to inventory
					inventory.push_back("HEALTH-POTION");
					cout << "ITEM OBTAINED: HEALTH-POTION" << endl << endl;
					library->setHealthPotionFound(true);
					pause();
				}
			}
			else
			{
				cout << "You've already looked here!" << endl << endl;
				pause();
			}
		}
		else if (choice == 3)
		{
			resetConsole();
			cout << "You check the fireplace..." << endl;
			cout << "A bat flies out and bites you in the face!" << endl << endl;
			health -= 5;

			//if the bat kills you, end the game
			if (health <= 0)
			{
				isDead = true;
				choice = 4;
			}

			pause();
		}
		else if (choice != 4)
			cout << "Invalid choice. Enter a menu option instead:" << endl;

	} while (choice != 4);
}

/*********************************************************************
** Function: Game::searchTreasury
**
** Description: The search function for the Treasury room. The user
** decides where they would like to search. Some options contain items
** and other options contain dangers. 
*********************************************************************/
void Game::searchTreasury()
{
	int choice;

	do
	{
		resetConsole();

		cout << "What would you like to search?" << endl;
		cout << "1. Check behind the chest." << endl;
		cout << "2. Check the treasure on the right." << endl;
		cout << "3. Check the treasure on the left." << endl;
		cout << "4. Back to room menu." << endl;
		cout << endl;

		//input validation
		choice = getInteger("Enter your choice:");

		while (choice <= 0 || choice > 4)
			choice = getInteger("Invalid choice. Enter a menu option instead:");

		cout << endl;

		if (choice == 1)
		{
			resetConsole();
			cout << "You check behind the chest..." << endl;
			cout << "A rat jumps out and bites you in the face!" << endl << endl;
			health -= 5;

			//if the rat kills you, end the game
			if (health <= 0)
			{
				isDead = true;
				choice = 4;
			}

			pause();
		}
		else if (choice == 2)
		{
			resetConsole();
			cout << "You search the treasure on the right..." << endl;

			//if you haven't already recieved the item
			if (!searchDiscardPile("GIANT-RUBY") && !searchInventory("GIANT-RUBY"))
			{
				cout << "There's too much treasure to possibly carry, but a GIANT-RUBY catches your eye!" << endl << endl;

				//verify inventory has space
				if (inventory.size() == MAX_INVENTORY)
				{
					cout << "Though you have no room to pick it up...manage your inventory first!" << endl;
					pause();
				}
				else
				{
					//add KING'S-ROBES to inventory
					inventory.push_back("GIANT-RUBY");
					cout << "ITEM OBTAINED: GIANT-RUBY" << endl << endl;
					pause();
				}
			}
			else
			{
				cout << "You've already looked here!" << endl << endl;
				pause();
			}
		}
		else if (choice == 3)
		{
			resetConsole();
			cout << "You search the treasure on the left..." << endl;

			//if you haven't already recieved the item
			if (!searchDiscardPile("JEWELED-CHALICE") && !searchInventory("JEWELED-CHALICE"))
			{
				cout << "There's too much treasure to possibly carry, but a JEWELED-CHALICE catches your eye!" << endl << endl;

				//verify inventory has space
				if (inventory.size() == MAX_INVENTORY)
				{
					cout << "Though you have no room to pick it up...manage your inventory first!" << endl;
					pause();
				}
				else
				{
					//add KING'S-ROBES to inventory
					inventory.push_back("JEWELED-CHALICE");
					cout << "ITEM OBTAINED: JEWELED-CHALICE" << endl << endl;
					pause();
				}
			}
			else
			{
				cout << "You've already looked here!" << endl << endl;
				pause();
			}
		}
		else if (choice != 4)
			cout << "Invalid choice. Enter a menu option instead:" << endl;

	} while (choice != 4);
}

/*********************************************************************
** Function: Game::searchTower
**
** Description: The search function for the Tower room. If the user
** killed the dragon but wasn't able to get the DUNGEON-KEY, then this
** function allows them to obtain it. 
*********************************************************************/
void Game::searchTower()
{
	resetConsole();

	//if the DUNGEON-KEY was already obtained, notify the user
	if (searchInventory("DUNGEON-KEY"))
		cout << "There's nothing here but a dead dragon..." << endl;
	//otherwise, grab the DUNGEON-KEY
	else
	{
		if (inventory.size() == MAX_INVENTORY)
		{
			cout << "You already have too much stuff...manage your inventory first!" << endl;
		}
		else
		{
			cout << "You retrieve the DUNGEON-KEY from the dragon's stomach...Gross!" << endl << endl;
			inventory.push_back("DUNGEON-KEY");
			cout << "ITEM OBTAINED: DUNGEON-KEY" << endl << endl;
		}
	}

	pause();
}

/*********************************************************************
** Function: Game::searchInventory
**
** Description: Iterates through the inventory to find a certain
** item. Different game logic occurs depending on the items in the 
** inventory, so it is necessary to be able to check which items the 
** player currently possesses
**
** Parameters: Takes a string as input, which represents the item name.
**
** Return: Returns true if the item was found in the inventory, and
** returns false if the item wasn't found.
*********************************************************************/
bool Game::searchInventory(std::string val)
{
	//itarate through the inventory, if the item is found return true
	for (list<string>::iterator i = inventory.begin(); i != inventory.end(); i++)
	{
		if (*i == val)
			return true;
	}
	return false;
}

/*********************************************************************
** Function: Game::searchDiscardPile
**
** Description: Iterates through the discard pile to find a certain
** item. Used to determine whether or not a particular item has already
** been found.
**
** Parameters: Takes a string as input, which represents the item name.
**
** Return: Returns true if the item was found in the discard pile, and
** returns false if the item wasn't found. 
*********************************************************************/
bool Game::searchDiscardPile(std::string val)
{
	//itarate through the discard pile, if the item is found return true
	for (list<string>::iterator i = discardPile.begin(); i != discardPile.end(); i++)
	{
		if (*i == val)
			return true;
	}
	return false;
}

/*********************************************************************
** Function: Game::removeItem
**
** Description: Used when the user selects "Manage Inventory". The 
** inventory contents are displayed and numbered. The user enters the 
** number of the item they wish to discard. If the item is not vital
** to the game plot, the item is removed from the player's inventory
** and placed into the discard pile. 
*********************************************************************/
void Game::removeItem()
{
	int count = 1;

	resetConsole();

	//display inventory
	cout << endl;
	cout << "Which item would you like to remove?" << endl;
	for (list<string>::iterator i = inventory.begin(); i != inventory.end(); i++)
	{
		cout << count << ". " << *i << endl;
		count++;
	}	
	cout << count << ". Nevermind" << endl << endl;

	//ask the user which item they want to remove
	int choice = getInteger("Enter your choice:");

	//validate input
	while (choice <= 0 || choice > count)
	{
		cout << "Invalid choice. Please enter one of the listed items instead." << endl;
		choice = getInteger("Enter your choice:");
	}

	//if the user doesn't choose "nevermind", remove the selected item
	if (choice < count)
	{
		int countTwo = 0;
		int value = choice - 1;
		std::string item;

		//find the item that needs to be removed
		for (list<string>::iterator i = inventory.begin(); i != inventory.end(); i++)
		{
			if (countTwo == value)
				item = *i;

			countTwo++;
		}

		cout << endl;

		//check to make sure the item isn't necessary to the plot
		if (item == "UNLIT-TORCH" || item == "LIT-TORCH")
		{
			cout << "You'll need this to see! Better hold onto it..." << endl << endl;
			pause();
		}
		else if (item == "MIRROR" && !searchInventory("LIT-TORCH"))
		{
			cout << "Wait, maybe you could use this to light your torch..." << endl << endl;
			pause();
		}
			
		else if (item == "ROYAL-JEWEL")
		{
			cout << "But the PRINCESS said we need this to access a hidden room..." << endl;
			cout << "Better hold onto it." << endl << endl;
			pause();
		}
		else if (item == "GOLDEN-SHIELD" || item == "HERO'S-SWORD")
		{
			cout << "You'll need this for protection! Better hold onto it..." << endl << endl;
			pause();
		}
		else if (item == "DUNGEON-KEY")
		{
			cout << "No...you need this to save the PRINCESS. Remember?" << endl << endl;
			pause();
		}	
		//if the item is not necessary, remove it and add it to the discard pile
		else
		{
			inventory.remove(item); 
			discardPile.push_back(item); 
			cout << "You have removed: " << item << endl << endl;
			pause();
		}	
	}
}

/*********************************************************************
** Function: Game::winScreen
**
** Description: Clears the console and displays the win screen.
*********************************************************************/
void Game::winScreen()
{
	//clear the console
	cout << "\033[2J\033[1;1H";

	//display health and inventory
	cout << "HEALTH: " << health << endl;
	cout << "INVENTORY: ";
	for (list<string>::iterator i = inventory.begin(); i != inventory.end(); i++)
		cout << *i << "  ";
	cout << endl;

	//display the win screen
	string imageLines = "";
	string fileName;

	ifstream inputFile;

	fileName = "win.txt";

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

	//display final text
	cout << endl;
	cout << "The PRINCESS is saved!" << endl << endl;
	cout << "You weren't able to rob the place blind, but hey, this GOLDEN-SHIELD" << endl;
	cout << "has to be worth something right?" << endl << endl;
	cout << "PRINCESS: Thank you so much for saving me! *Kisses you on the cheek*" << endl;
	cout << "          Now we can go save my father from the evil Wizard!" << endl << endl;
	cout << "\"Screw that!\" you yell, then you run off into the woods" << endl << endl;
	cout << "THE END" << endl << endl;
	pause();
}

/*********************************************************************
** Function: Game::loseScreen
**
** Description: Clears the console and displays the losing screen. 
*********************************************************************/
void Game::loseScreen()
{
	//clear the console
	cout << "\033[2J\033[1;1H";

	//display health and inventory
	cout << "HEALTH: " << health << endl;
	cout << "INVENTORY: ";
	for (list<string>::iterator i = inventory.begin(); i != inventory.end(); i++)
		cout << *i << "  ";
	cout << endl;
	
	//display the lose screen
	string imageLines = "";
	string fileName;

	ifstream inputFile;

	fileName = "lose.txt";

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

	//display final text
	cout << endl;
	cout << "Looks like you weren't able to save the PRINCESS..." << endl << endl;
	pause();
}

/*********************************************************************
** Function: Game::resetConsole
**
** Description: Clears the console, then reprints the inventory and
** room image. 
*********************************************************************/
void Game::resetConsole()
{
	//clear the console
	cout << "\033[2J\033[1;1H";

	//display health and inventory
	cout << "HEALTH: " << health << endl;
	cout << "INVENTORY: ";
	for (list<string>::iterator i = inventory.begin(); i != inventory.end(); i++)
		cout << *i << "  ";
	cout << endl;

	//display room image
	location->displayImage();
}

/*********************************************************************
** Function: Game::pause
**
** Description: Waits for the user to press Enter before moving on 
** with the game. Uses getline for user input.
*********************************************************************/
void Game::pause()
{
	//wait for the user to press enter before continuing 
	string temp;
	cout << "PRESS ENTER TO CONTINUE" << endl;
	getline(cin, temp);
	cin.clear();
	cin.ignore();
	cout << "\033[2J\033[1;1H";
}

/*********************************************************************
** Function: Game::getInteger
**
** Description: Input validation function for integers.
**
** Parameters: A single string, which is the prompt that asks the user
** for a specific input.
**
** Return: Returns an integer which has been verified to be a
** non-negative and non-zero integer.
*********************************************************************/
int Game::getInteger(std::string prompt)
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