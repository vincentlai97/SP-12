#include "game.h"

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