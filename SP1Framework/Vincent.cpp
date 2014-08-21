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

bool createEnemy (enemies enemyArr[], int size, int width, int height, char** enemy, int y)
{
	for (int count = 0; count < size; count++)
	{
		if (enemyArr[count].size[0] == 0)
		{
			enemyArr[count].set(80, y, width, height, 1);

			enemyArr[count].setlook(enemy);

			return 1;
		}
	}
	return 0;
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

bool checkBulletCollision(enemies enemyArr[], int size)
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
						return 1;
					}
				}
			}
		}
	}
	return 0;
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

void initAste ()
{
	enemyaste = new char*[1];
	enemyaste[0] = new char [3];

	enemyaste[0][0] = '@';
	enemyaste[0][1] = '}';
	enemyaste[0][2] = '=';
}

void moveCat (int size)
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

void moveAste (int size)
{
	for (int count = 0; count < size; count++)
	{
		if (asteArr[count].size[0])
		{
			asteArr[count].location.X--;
		}
	}
}

void createCat (int num)
{
	const int y = 1;
	createEnemy(catArr, num, 2, 3, enemycat, y);
}

void createAste (int num)
{
	int y = rand() % 21 + 1;
	createEnemy(asteArr, num, 1, 3, enemyaste, y);
}

void checkEnemyCollision (enemies enemyArr[], int size)
{
	for (int count = 0; count < size; count++)
	{
		if (enemyArr[count].location.X >= 1 - enemyArr[count].size[0] + shipLocation.X && 
			enemyArr[count].location.X <= shipLen + shipLocation.X &&
			enemyArr[count].location.Y >= -1 - enemyArr[count].size[1] + shipLocation.Y &&
			enemyArr[count].location.Y <= 2 + shipLocation.Y)
		{
			enemyArr[count].size[0] = 0;
			enemyArr[count].size[0] = 0;
		}
	}
}

bool Levelcat (int level)
{
	int num = (level == 1 ? 10 : (level == 2 ? 20 : 40));

	static int counter = 0;

	if (!(counter++%3) && counter <= num*3)
		createCat(num);

	if (checkBulletCollision(catArr, num)) score += num;
	moveCat(num);
	renderEnemy(catArr, num);
	if (checkBulletCollision(catArr, num)) score += num;
	checkEnemyCollision(catArr, num);

	return checkClear(catArr, num);
}

bool Levelaste (int level)
{
	int num = (level == 1 ? 20 : (level == 2 ? 40 : 60));

	static int counter = 0;

	if (counter < num && (!counter || rand() % 100 > (90 - level)))
	{
		createAste(num);
		counter++;
	}

	if (checkBulletCollision(asteArr, num)) score += 10;
	moveAste(num);
	renderEnemy(asteArr, num);
	if (checkBulletCollision(asteArr, num)) score += 10;
	checkEnemyCollision(asteArr, num);

	return checkClear(asteArr, num);
}

bool checkClear (enemies enemyArr[], int size)
{
	for (int count = 0; count < size; count++)
	{
		if (enemyArr[count].size[0])
			return 0;
	}
	return 1;
}