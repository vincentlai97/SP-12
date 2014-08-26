// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
unsigned int bulletBuffer;
COORD shipLocation;
COORD consoleSize;
char ship[5][20];
size_t shipLen;
int bullets[80] = {0};
int score;
int Life;
enemies* enemyArr;
int number;
bool alwaysMove;
int x_maxmove;
int y_maxmove;
bool limit;
int x_limit[LIMIT];
int y_limit[LIMIT];
int spawnChance;
int spawnBuffer;
int spawnBufferCount;
bool setSpawn;
int spawnLocation;
int enemySpawned;

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    /*shipLocation.X = consoleSize.X / 2;
    shipLocation.Y = consoleSize.Y / 2;*/

	shipLocation.X = 0;
	shipLocation.Y = consoleSize.Y / 2 - 3;

	shipLen = strlen(ship[2]);

	for (int count = 0; count <80; count++)
		bullets[count] = 0;
	
	bulletBuffer = 0;

	spawnBufferCount = 0;
	
	Life = 3;

	enemySpawned = 0;

    elapsedTime = 0.0;	
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	exit (1);
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && shipLocation.Y > 2)
    {
        Beep(1440, 10);
        shipLocation.Y--;

    }
    if (keyPressed[K_LEFT] && shipLocation.X > 0)
    {
        Beep(1440, 10);
        shipLocation.X--;
    }
    if (keyPressed[K_DOWN] && shipLocation.Y < consoleSize.Y - 3)
    {
        Beep(1440, 10);
        shipLocation.Y++;
    }
    if (keyPressed[K_RIGHT] && shipLocation.X < consoleSize.X - strlen(ship[3]))
    {
        Beep(1440, 10);
        shipLocation.X++;
    }

	if (keyPressed[K_SPACE] && bulletBuffer == 0)
	{
		bullets[shipLocation.X + shipLen] = shipLocation.Y;
		bulletBuffer += 5;
	}
	else
	{
		bullets[shipLen] = 0;
		bulletBuffer -= (bulletBuffer <= 0 ? 0 : 1);
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		DisplayInGame();
	}
        //g_quitGame = true;    
}

void render()
{
    // clear previous screen
    colour(0x0F);
    cls();

    //render the game

    //render test screen code (not efficient at all)
    /*const WORD colors[] =   {
	                        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	                        };
	
	for (int i = 0; i < 12; ++i)
	{
		gotoXY(3*i,i+1);
		colour(colors[i]);
		std::cout << "WOW";
	}*/

    // render time taken to calculate this frame
    gotoXY(0, 1);
    colour(0x10A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x10A);
    std::cout << elapsedTime << "secs" << std::endl;

    renderShip();
	renderBullets();
	checkBulletCollision(enemyArr, number);

	for (static int levelStart = false; levelStart == false;)
		levelStart = initLevel(11);

	if (!spawnBufferCount && enemySpawned <= 10)
	{
		spawnEnemy();
		spawnBufferCount += spawnBuffer;
		enemySpawned++;
	}
	else spawnBufferCount--;
	moveEnemy(enemyArr, number);
	checkBulletCollision(enemyArr, number);
	renderEnemy(enemyArr, number);
	if (checkEnemyCollision(enemyArr, number)) Life--;
	
	CurrentScore();
	LifeCounter();
}

void renderShip()
{
	for (int count = -2; count <= 2; count++)
	{
		gotoXY(shipLocation.X, shipLocation.Y + count);
		colour(0x0C);
		std::cout << ship[2 + count];
	}
}

bool initEnemies (char* enemy, int number)
{
	int height, width, life;
	char** model;

	std::ifstream Model;
	Model.open("Models.txt");

	char data[100];

	while (Model.getline(data, 100))
	{
		if (!strcmp(data, enemy))
		{
			Model.getline(data, 100, '=');
			if (strstr (data, "height"))
			{
				Model >> height;
				Model.getline(data, 100, '=');
			}
			if (strstr (data, "width"))
			{
				Model >> width;
				Model.getline(data, 100, '=');
			}
			if (strstr (data, "life"))
			{
				Model >> life;
				Model.getline(data, 100, '=');
			}
			if (strstr (data, "model"))
			{
				Model.getline(data, 100);
				model = new char*[height];
				for (int count = 0; count < height; count++)
				{
					model[count] = new char[width];
					Model.getline(data, 100);
					for (int count2 = 0; count2 < width; count2++)
						model[count][count2] = data[count2];
				}
			}
		}
	}

	Model.close();

	enemyArr = new enemies[number];
	for (int count = 0; count < number; count++)
	{
		enemyArr[count].set(height, width, life);
		enemyArr[count].setModel(model);
	}

	delete[] model;

	return 1;
}

bool initLevel (int level)
{
	char buffer[10] = {"LEVEL "}, buffer2[10];
	char enemy[100];

	std::ifstream Level;
	Level.open("Levels.txt");

	char data[100];
	strcat(buffer, itoa(level, buffer2, 10));

	while (Level.getline(data, 100))
	{
		if (!strcmp(data, buffer))
		{
			Level.getline(data, 100, '=');
			if (strstr(data, "enemy"))
			{
				Level >> std::ws;
				Level.getline(data, 100);
				strcpy(enemy, data);
				Level.getline(data, 100, '=');
			}
			if (strstr(data, "number"))
			{
				Level >> number;
				Level.getline(data, 100, '=');
			}
			if (strstr(data, "alwaysmove"))
			{	
				Level >> std::boolalpha >> alwaysMove;
				Level.getline(data, 100, '=');
			}
			if (strstr(data, "x_maxmove"))
			{
				Level >> x_maxmove;
				Level.getline(data, 100, '=');
			}
			if (strstr(data, "y_maxmove"))
			{
				Level >> y_maxmove;
				Level.getline(data, 100, '=');
			}
			if (strstr(data, "limit"))
			{
				Level >> std::boolalpha >> limit;
				if (limit)
				{
					Level.getline(data, 100, '=');
					if (strstr(data, "x_limit"))
					{
						Level >> x_limit[LOWER];
						Level >> x_limit[UPPER];
					}
					Level.getline(data, 100, '=');
					if (strstr(data, "y_limit"))
					{
						Level >> y_limit[LOWER];
						Level >> y_limit[UPPER];
					}
				}
				else
				{
					x_limit[LOWER] = 0;
					x_limit[UPPER] = 80;
					y_limit[LOWER] = 1;
					y_limit[UPPER] = 22;
				}
				Level.getline(data, 100, '=');
			}
			if (strstr(data, "spawnchance"))
			{
				Level >> spawnChance;
				Level.getline(data, 100, '=');
			}
			if (strstr(data, "spawnbuffer"))
			{
				Level >> spawnBuffer;
				Level.getline(data, 100, '=');
			}
			if (strstr(data, "setspawn"))
			{
				Level >> std::boolalpha >> setSpawn;
				if (setSpawn)
				{
					Level.getline(data, 100, '=');
					if (strstr(data, "spawnlocation"))
						Level >> spawnLocation;
				}
				Level.getline(data, 100, '=');
			}
			break;
		}
	}

	Level.close();

	if (initEnemies(enemy, number)) return 1;
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
	if (enemy.location.X && enemy.location.Y)
	{
		for (int count2 = 0; count2 < enemy.size[HEIGHT]; count2++)
		{
			gotoXY(enemy.location.X, enemy.location.Y + count2);
			for (int count3 = 0; count3 < enemy.size[WIDTH]; count3++)
				if (enemy.location.X + count3 < 80)
					std::cout << enemy.model[count2][count3];
		}

		if(!enemy.location.X)
		{
			enemy.location.Y = 0;
		}
	}
}

int spawnEnemy()
{
	for (int count = 0; count < number; count++)
		if (!(enemyArr[count].location.X || enemyArr[count].location.Y))
			if (spawnEnemy(enemyArr[count]))
				return spawnBuffer;
}

bool spawnEnemy (enemies& enemy)
{
	if (setSpawn)
	{
		enemy.location.X = 80;
		enemy.location.Y = spawnLocation;
	}
	else
	{
		enemy.location.X = 70;
		enemy.location.Y = rand() % 22 + 1;
	}
	enemy.direction[DIRECTION_X] = x_maxmove;
	enemy.direction[DIRECTION_Y] = y_maxmove;
	return 1;
}

void moveEnemy (enemies enemyArr[], int size)
{
	for (int count = 0; count < size; count++)
		moveEnemy(enemyArr[count]);
}

void moveEnemy (enemies& enemy)
{
	if (enemy.location.X && enemy.location.Y)
	{
		if (alwaysMove)
		{
			moveEnemy(enemy, enemy.direction[DIRECTION_X], enemy.direction[DIRECTION_Y]);
			if (enemy.location.Y == 1)
				enemy.direction[DIRECTION_Y] = abs(y_maxmove);
			else if (enemy.location.Y == 22)
				enemy.direction[DIRECTION_Y] = -abs(y_maxmove);
			
		}
		else
		{
			if (!(enemy.direction[DIRECTION_X] || enemy.direction[DIRECTION_Y]))
			{
				switch (rand()%4)
				{
				case UP: enemy.direction[DIRECTION_Y] += rand()%y_maxmove + 1;
					break;
				case DOWN: enemy.direction[DIRECTION_Y] -= rand()%y_maxmove + 1;
					break;
				case LEFT: enemy.direction[DIRECTION_X] += rand()%x_maxmove + 1;
					break;
				case RIGHT: enemy.direction[DIRECTION_X] -= rand()%x_maxmove + 1;
					break;
				}
			}
			moveEnemy(enemy, enemy.direction[DIRECTION_X], enemy.direction[DIRECTION_Y]);
		}
	}
}

void moveEnemy (enemies& enemy, int& x, int& y)
{
	if (x > 0)
	{
		if (enemy.location.X > x_limit[LOWER])
			enemy.location.X--;
	}
	else if (x < 0)
	{
		if (enemy.location.X < x_limit[UPPER])
			enemy.location.X++;
	}
	if (y > 0)
	{
		if (enemy.location.Y < y_limit[UPPER])
			enemy.location.Y++;
	}
	else if (y < 0)
	{
		if (enemy.location.Y > y_limit[LOWER])
			enemy.location.Y--;
	}
	if (enemy.location.X <= 0)
	{
		enemy.location.Y = 0;
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
					if (!--enemy.life)
					{
						enemy.size[0] = 0;
						enemy.size[1] = 0;
					}
					return 1;
				}
			}
		}
	}
	return 0;
}

bool checkEnemyCollision (enemies enemyArr[], int size)
{
	for (int count = 0; count < size; count++)
	{
		if (enemyArr[count].size[0] && enemyArr[count].size[1])
		{
			if (enemyArr[count].location.X >= 1 - enemyArr[count].size[0] + shipLocation.X && 
				enemyArr[count].location.X <= shipLen + shipLocation.X &&
				enemyArr[count].location.Y >= -1 - enemyArr[count].size[1] + shipLocation.Y &&
				enemyArr[count].location.Y <= 2 + shipLocation.Y)
			{
				enemyArr[count].size[0] = 0;
				enemyArr[count].size[1] = 0;
				return 1;
			}
		}
	}
	return 0;
}