#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

void renderShip()
{
	for (int count = -2; count <= 2; count++)
	{
		gotoXY(shipLocation.X, shipLocation.Y + count);
		colour(0x0C);
		for (int count2 = 0; count2 < 12; count2++)
			std::cout << ship[(2+count)*12 + count2];
	}
}

void renderBullets ()
{
	for (int count = 0; count < consoleSize.X - 12; count++)
	{
		if (bullets[count])
		{
			gotoXY(12 + count, bullets[count]);
			std::cout << '_';
		}
	}

	for (int count = consoleSize.X - 12; count > 0; count--)
	{
		bullets[count] = bullets[count - 1];
	}
}