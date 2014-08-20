#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>

void chooseShip(int shipNum)
{
	char ship1[5][20] =
	{
		"__",
		"| \\",
		"=[_H)--.____",
		"=[+-,------'",
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

void CurrentScore()
{
	gotoXY(35,0);
	colour(0x10A);
	std::cout << "score: " << score << std::endl;
}