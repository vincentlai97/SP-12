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
		std::cout << ship[2 + count];
	}
}

void renderBullets ()
{
	for (int count = 0; count < consoleSize.X - shipLen; count++)
	{
		if (bullets[count])
		{
			gotoXY(shipLen + count, bullets[count]);
			std::cout << '_';
		}
	}

	for (int count = consoleSize.X - shipLen; count > 0; count--)
	{
		bullets[count] = bullets[count - 1];
	}
}

void renderEnemies ()
{

}