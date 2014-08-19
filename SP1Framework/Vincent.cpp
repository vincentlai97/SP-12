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
			std::cout << '-';
		}
	}

	for (int count = consoleSize.X - shipLen; count > 0; count--)
	{
		bullets[count] = bullets[count - 1];
	}
}

void createEnemy ()
{
	char** cat; int catw = 2, cath = 3;
    enemyNum[1].set(67, 3, catw, cath);

	cat = new char*[catw];
	for (int count = 0; count < cath; count++)
	{
		cat[count] = new char[cath];
	}

	cat[0][0] = static_cast<char>(148); cat[0][1] = static_cast<char>(95); cat[0][2] = static_cast<char>(159); cat[1][0] = static_cast<char>(234); cat[1][1] = static_cast<char>(208); cat[1][2] = static_cast<char>(234);

	enemyNum[1].setlook(cat);


}

void renderEnemy()
{
	for (int count = 0; count < 10; count++)
	{
		if (enemyNum[count].size[0] && enemyNum[count].size[1])
		{
			for (int count2 = 0; count2 < enemyNum[count].size[0]; count2++)
			{
				gotoXY(enemyNum[count].location.X, enemyNum[count].location.Y + count2);
				for (int count3 = 0; count3 < enemyNum[count].size[1]; count3++)
					std::cout << enemyNum[count].look[count2][count3];
			}

			if(enemyNum[count].location.X)
				enemyNum[count].location.X--;
			else
			{
				enemyNum[count].size[0] = 0;
				enemyNum[count].size[1] = 0;
			}
		}
	}
}

void checkBulletCollision()
{
	for (int count = 0; count < consoleSize.X - shipLen; count++)
	{
		if (bullets[count])
		{
			for (int count2 = 0; count2 < 10; count2++)
			{
				for (int count3 = 0; count3 < enemyNum[count2].size[0]; count3++)
				{
					if (count + shipLen == enemyNum[count2].location.X && bullets[count] == enemyNum[count2].location.Y)
					{
						bullets[count] = 0;
						enemyNum[count2].size[0] = 0;
						enemyNum[count2].size[1] = 0;
					}
				}
			}
		}
	}
}