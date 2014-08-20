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
	for (int count = shipLen; count < consoleSize.X; count++)
	{
		if (bullets[count])
		{
			gotoXY(count, bullets[count]);
			std::cout << '-';
		}
	}

	for (int count = consoleSize.X; count > shipLen; count--)
	{
		bullets[count] = bullets[count - 1];
	}
}

void createEnemy (int width, int height, char** enemy)
{
	for (int count = 0; count < 10; count++)
	{
		if (enemyNum[count].size[0] == 0)
		{
			enemyNum[count].set(80, rand() % 21 + 2, width, height);

			enemyNum[count].setlook(enemy);

			break;
		}
	}

}

void createEnemy (char enemy)
{
	switch (enemy)
	{
	case 99:
		createEnemy (2, 3, enemycat);
		break;
	}
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
					if (enemyNum[count].location.X + count3 < 80)
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
	for (int count = shipLen; count < consoleSize.X; count++)
	{
		if (bullets[count])
		{
			for (int count2 = 0; count2 < 10; count2++)
			{
				for (int count3 = 0; count3 < enemyNum[count2].size[0]; count3++)
				{
					if (count == enemyNum[count2].location.X && bullets[count] == enemyNum[count2].location.Y + count3)
					{
						bullets[count] = 0;
						enemyNum[count2].size[0] = 0;
						enemyNum[count2].size[1] = 0;
						score++;
					}
				}
			}
		}
	}
}

void initCat ()
{
	enemycat = new char* [2];
	for (int count = 0; count < 2; count ++)
		enemycat[count] = new char [3];

	enemycat[0][0] = static_cast<char>(148);
	enemycat[0][1] = static_cast<char>(95);
	enemycat[0][2] = static_cast<char>(159);
	enemycat[1][0] = static_cast<char>(234);
	enemycat[1][1] = static_cast<char>(208);
	enemycat[1][2] = static_cast<char>(234);
}