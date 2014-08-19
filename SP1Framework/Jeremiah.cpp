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
	cout << "  #######  " << " " << "########   " << endl;
	cout << " ######### " << " " << "###   #### " << endl;
	cout << "####    ###" << " " << "###    ####" << endl;
	cout << " ####      " << " " << "###   #### " << endl;
	cout << "   ####    " << " " << "########   " << endl;
	cout << "      #### " << " " << "###        " << endl;
	cout << "       ####" << " " << "###        " << endl;
	cout << "###    ####" << " " << "###        " << endl;
	cout << " ######### " << " " << "###        " << endl;
	cout << "  #######  " << " " << "### SPACE PUSSY" << endl;
	cout << endl;
	cout << "1 - Start" << endl << "2 - Options" << endl << "3 - Exit" << endl;
	cout << "Enter the choie you want and press enter" << endl;
}

void DisplayOptions()
{
	cout << "Sound" << endl;
	cout << "Options" << endl;
	cout << "1 - Start" << endl;
	cout << "3 - Exit" << endl;
}

void DisplayInGame()
{
	cout << "2 - Options" << endl;
	cout << " 3 - Options" << endl;
}
