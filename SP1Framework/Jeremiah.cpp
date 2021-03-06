#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;

const unsigned char FPS = 20; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

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
	cout << endl << endl << endl;
	cout << "                             #######  " << " " << "########   " << endl;
	cout << "                            ######### " << " " << "###   #### " << endl;
	cout << "                           ####    ###" << " " << "###    ####" << endl;
	cout << "                            ####      " << " " << "###   #### " << endl;
	cout << "                              ####    " << " " << "########   " << endl;
	cout << "                                 #### " << " " << "###        " << endl;
	cout << "                                  ####" << " " << "###        " << endl;
	cout << "                           ###    ####" << " " << "###        " << endl;
	cout << "                            ######### " << " " << "###        " << endl;
	cout << "                             #######  " << " " << "### SPACE PEWTER" << endl;
	cout << endl;
	cout << "                                1 - Start" << endl;
	cout << "                                2 - Options" << endl;
	cout << "                                3 - Choose Ship" << endl;
	cout << "                                4 - Exit Game" << endl;
	cout << "                    Enter the choice you want and press enter" << endl;
	cout << "                                      ";
	Selection();
	return;
}

void DisplayOptions()
{
	colour(0x10A);
	cls();
	cout << "Sound" << endl;
	cout << "Options" << endl;
	cout << "1 - Back" << endl;
	cout << "2 - Exit" << endl;
	int H = 0;
	H = getKey();

	switch ( H )
	{
	case 1: DisplayMainMenu();
		break;
	case 2: shutdown();
		break;
	}
	return;
}

void DisplayInGame()
{
	gotoXY(35,5);
	colour(0x10A);
	cls();
	cout << endl << endl << endl << endl;
	cout << "                        ****  " << " ****  " << "*    * " << "***** " << "***** " << endl;
	cout << "                        *   * " << "*    * " << "*    * " << "*     " << "*     " << endl;
	cout << "                        ****  " << "****** " << "*    * " << "***** " << "***** " << endl;
	cout << "                        *     " << "*    * " << "*    * " << "    * " << "*     " << endl;
	cout << "                        *     " << "*    * " << " ****  " << "***** " << "***** " << endl;
	cout << "                                1 - Restart" << endl;
	cout << "                                2 - Exit Game" << endl;
	cout << "                                3 - Back to Main Menu" << endl;
	cout << "                                     ";
	int H = 0;
	H = getKey();

	switch ( H )
	{
	case 1: init(); 
		gRestart();
		break;
	case 2: shutdown();
		break;
	case 3: DisplayMainMenu();
		break;
	}
	return;
}

void Pause()
{
	//system("pause");
	DisplayInGame();
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
	cout << endl << "1 - X-Wing" << endl << "2 - Arrowhead" << endl << "3 - Main Menu" << endl;
	int shipNum = 1;

	cin >> shipNum;

	switch (shipNum)
	{
	case 1:
		for (int count = 0; count < 5; count++)
		{
			strcpy(ship[count], ship1[count]);
		}
		init();
		mainLoop();
		break;
	case 2:
		for (int count = 0; count < 5; count++)
		{
			strcpy(ship[count], ship2[count]);
		}
		init();
		mainLoop();
		break;
	case 3: DisplayMainMenu();
		Selection();
		break;
	default: 
		for (int count = 0; count < 5; count++)
		{
			strcpy(ship[count], ship1[count]);
		}
		init();
		mainLoop();
		break;
	}
}

void gRestart()
{
	g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!g_quitGame)      // run this loop until user wants to quit 
	{        
		getInput();                         // get keyboard input
		update(g_timer.getElapsedTime());   // update the game
		render();                           // render the graphics output to screen
		g_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.      
	}    
}

void Selection()
{
	int choice = 0;
	do
	{
		choice = getKey();
		switch(choice)
		{
		case 1: ChangeShip();
			break;
		case 2: DisplayOptions();
			break;
		case 3: ChangeShip();
			break;
		case 4: shutdown();
		default:
			break;
		}
	} while ( choice != 4 );
}

void GameOver()
{
	init(); 
	cls();
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "                                  GAME OVER" << endl;
	cout << "                                  1.Continue? " << endl;
	cout << "                                  2.Main Menu" << endl;
	cout << "                                  3.Exit" << endl;
	cout << "                                   " << endl;
	int H = 0;
	H = getKey();

	switch ( H )
	{
	case 1: init();
		gRestart();
		break;
	case 2: DisplayMainMenu();
		break;
	case 3: shutdown();
		break;
	}
	return;
}