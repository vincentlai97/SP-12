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
			std::cout << "-";
		}
	}

	for (int count = consoleSize.X -1; count > shipLen; count--)
	{
		bullets[count] = bullets[count - 1];
	}
}

//void createEnemy (int width, int height, char** enemy, int y)
//{
//	for (int count = 0; count < 10; count++)
//	{
//		if (enemyNum[count].size[0] == 0)
//		{
//			enemyNum[count].set(80, y, width, height, 1);
//
//			enemyNum[count].setlook(enemy);
//
//			break;
//		}
//	}
//
//}

void createEnemy (char enemy)
{
	switch (enemy)
	{
	case 99:
		createCat (10);
		break;
	}
}

void renderEnemy(enemies enemyArr[], int size)
{
	for (int count = 0; count < size; count++)
	{
		if (enemyArr[count].size[0] && enemyArr[count].size[1])
		{
			for (int count2 = 0; count2 < enemyArr[count].size[0]; count2++)
			{
				gotoXY(enemyArr[count].location.X, enemyArr[count].location.Y + count2);
				for (int count3 = 0; count3 < enemyArr[count].size[1]; count3++)
					if (enemyArr[count].location.X + count3 < 80)
						std::cout << enemyArr[count].look[count2][count3];
			}

			if(!enemyArr[count].location.X)
			{
				enemyArr[count].size[0] = 0;
				enemyArr[count].size[1] = 0;
			}
		}
	}
}

void checkBulletCollision(enemies enemyArr[], int size)
{
	for (int count = shipLen; count < consoleSize.X; count++)
	{
		if (bullets[count])
		{
			for (int count2 = 0; count2 < size; count2++)
			{
				for (int count3 = 0; count3 < enemyArr[count2].size[0]; count3++)
				{
					if (count == enemyArr[count2].location.X && bullets[count] == enemyArr[count2].location.Y + count3)
					{
						bullets[count] = 0;
						enemyArr[count2].size[0] = 0;
						enemyArr[count2].size[1] = 0;
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

void moveCat(int size)
{
	for (int count = 0; count < size; count++)
	{
		if (catArr[count].size[0])
		{
			catArr[count].location.X--;
			if (!catArr[count].location.Y)
				catArr[count].dir = 1;
			else if (catArr[count].location.Y == 22)
				catArr[count].dir = 0;
			switch (catArr[count].dir)
			{
			case 0: catArr[count].location.Y--;
				break;
			case 1: catArr[count].location.Y++;
				break;
			}
		}
	}
}

void createCat (int Num)
{
	static int y = 1;
	for (int count = 0; count < Num; count++)
	{
		if (catArr[count].size[0] == 0)
		{
			catArr[count].set(80, y, 2, 3, 1);

			catArr[count].setlook(enemycat);

			y++;
			break;
		}
	}
}