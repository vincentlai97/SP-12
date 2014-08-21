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

bool createEnemy (enemies enemyArr[], int size, int width, int height, char** enemy, int y, int x)
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

void renderEnemy (enemies enemyArr[], int size)
{
	for (int count = 0; count < size; count++)
	{
		renderEnemy(enemyArr[count]);
	}
}

void renderEnemy (enemies& enemy)
{
	if (enemy.size[0] && enemy.size[1])
	{
		for (int count2 = 0; count2 < enemy.size[1]; count2++)
		{
			gotoXY(enemy.location.X, enemy.location.Y + count2);
			for (int count3 = 0; count3 < enemy.size[0]; count3++)
				if (enemy.location.X + count3 < 80)
					std::cout << enemy.look[count2][count3];
		}

		if(!enemy.location.X)
		{
			enemy.size[0] = 0;
			enemy.size[1] = 0;
		}
	}
}

bool checkBulletCollision(enemies enemyArr[], int size)
{
	for (int count = 0; count < size; count++)
	{
		if (checkBulletCollision(enemyArr[count])) return 1;
	}
	return 0;
}


bool checkBulletCollision(enemies& enemy)
{
	for (int count = shipLen; count < consoleSize.X; count++)
	{
		if (bullets[count])
		{
			for (int count2 = 0; count2 < enemy.size[1]; count2++)
			{
				if (count == enemy.location.X && bullets[count] == enemy.location.Y + count2)
				{
					bullets[count] = 0;
					enemy.size[0] = 0;
					enemy.size[1] = 0;
					return 1;
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
	createEnemy(catArr, num, 3, 2, enemycat, y);
}

void createAste (int num)
{
	int y = rand() % 21 + 1;
	createEnemy(asteArr, num, 3, 1, enemyaste, y);
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

void initBoss (int num)
{
	switch (num)
	{
	case 1:
		boss.set(70, 10, 30, 9, 1);
		boss.life = 30;

		char** boss1 = new char* [9];
		for (int count = 0; count< 9; count++)
			boss1[count] = new char[30];

		strcpy(boss1[0], "                      ______");
		strcpy(boss1[1], "                     /~~~~~|");
		strcpy(boss1[2], "                .__./''''''|");
		strcpy(boss1[3], "._____________/   |/^^^^^^^\\");
		strcpy(boss1[4], "|             `===\"\\_______/");
		strcpy(boss1[5], "`.             .___/^^^^^^^^\\");
		strcpy(boss1[6], "  `------------'~~~\\________/");
		strcpy(boss1[7], "                   `........\\");
		strcpy(boss1[8], "                    `-------'");

		boss.setlook(boss1);

		for (int count = 8; count >= 0; count--)
			delete[] boss1[count];
		delete[] boss1;

		bossBullet = new char* [1];
		bossBullet[0] = new char [3]; 
		for (int count = 0; count < 3; count++)
			bossBullet[0][count] = '-';

		break;
	}
}

bool levelBoss (int level)
{
	static int counter = 1;
	switch (level)
	{
	case 1: if (counter--) initBoss(level);
		break;
	}

	if (checkBulletCollision(boss)) boss.life--;
	moveBoss();
	renderEnemy(boss);
	if (checkBulletCollision(boss)) boss.life--;
	checkEnemyCollision(bossBullets, 20);

	return checkClear(bossBullets, 100);
}

void moveBoss()
{
	static int move = 0;

	switch (move)
	{
	case 0: boss.location.X -= (boss.location.X > 30);
		break;
	case 1: boss.location.X += (boss.location.X < 70);
		break;
	case 2: boss.location.Y -= (boss.location.Y > 0);
		break;
	case 3: boss.location.Y += (boss.location.Y < 15);
		break;
	}

	if ((rand() % 100) > 60)
		createEnemy(bossBullets, 20, 1, 3, bossBullet, boss.location.Y - 4, boss.location.X - 1);
}