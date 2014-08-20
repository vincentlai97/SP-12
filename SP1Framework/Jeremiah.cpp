#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;

int getKey()
{
	int choice;
	cin >> choice;
	return choice;
}

void DisplayMainMenu()
{
	colour(0x10A);
	cls();
	cout << "  #######  " << " " << "########   " << endl;
	cout << " ######### " << " " << "###   #### " << endl;
	cout << "####    ###" << " " << "###    ####" << endl;
	cout << " ####      " << " " << "###   #### " << endl;
	cout << "   ####    " << " " << "########   " << endl;
	cout << "      #### " << " " << "###        " << endl;
	cout << "       ####" << " " << "###        " << endl;
	cout << "###    ####" << " " << "###        " << endl;
	cout << " ######### " << " " << "###        " << endl;
	cout << "  #######  " << " " << "### SUPER PEWTER" << endl;
	cout << endl;
	cout << "1 - Start" << endl << "2 - Options" << endl  << "3 - Change Ship" << endl << "4 - Exit" << endl;
	cout << "Enter the choice you want and press enter" << endl;
}

void DisplayOptions()
{
	colour(0x10A);
	cls();
	cout << "Sound" << endl;
	cout << "Options" << endl;
	cout << "1 - Back" << endl;
	cout << "4 - Exit" << endl;
	int H = 0;
	H = getKey();

	switch ( H )
	{
	case 1: DisplayMainMenu();
		break;
	case 2: shutdown();
		break;
	}
}

void DisplayInGame()
{
	colour(0x10A);
	cls();
	cout << "1 - Back to the Title Screen" << endl;
	cout << "2 - Resume game" << endl;
	cout << "3 - Quit Game" << endl;
	int H = 0;
	H = getKey();
	switch(H)
	{
	case 1: DisplayMainMenu();
		break;
	case 2: system("resume");
		break;
	case 3: shutdown();
		break;
	}
}

void ChangeShip()
{
	char ship1[5][20] =
	{
		"__",
		"| \\",
		"}[_H)--.____",
		"}[+-,------'",
		" [_/"
	}; 
	char ship2[5][20] = 
	{
		"     /\\",
		" |\\  \\ \\",
		"| <====}>",
		" |/  / /",
		"     \\/"
	};

	colour(0x10A);
	cls();
	cout << "Choose the spaceship you want to use" << endl << endl;

	cout << "Ship 1" << endl;

	for (int count = -2; count <= 2; count++)
	{
		std::cout << ship1[2 + count] << endl;
	}
	cout << endl;

	cout << "Ship 2" << endl;

	for (int count = -2; count <= 2; count++)
	{
		std::cout << ship2[2 + count] << endl;
	}
	cout << endl << "Press 1 for Ship 1 and 2 for ship 2" << endl << "Then press 1 and enter to start the game" << endl;
	int shipNum = 1;

	cin >> shipNum;

	switch (shipNum)
	{
	case 1:
		for (int count = 0; count < 5; count++)
		{
			strcpy(ship[count], ship1[count]);
		}
		break;
	case 2:
		for (int count = 0; count < 5; count++)
		{
			strcpy(ship[count], ship2[count]);
		}
		break;
	}
}

