#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <string>
#include <string.h>
#include <vector>
#include <fstream>

using std::string;

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
	K_SPACE,	
    K_COUNT
};

enum dimension
{
	HEIGHT,
	WIDTH,
	DIMENSION
};

enum move
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MOVE
};

enum direction
{
	DIRECTION_X,
	DIRECTION_Y,
	DIRECTION
};

enum limit
{
	UPPER,
	LOWER,
	LIMIT
};

struct enemies
{
	COORD location;
	int size[DIMENSION];
	char** model;
	int life;
	int direction[DIRECTION];

	void set(int height, int width, int l)
	{
		size[HEIGHT] = height;
		size[WIDTH] = width;
		life = l;
		location.X = 0;
		location.Y = 0;
	}

	void setModel (char** extModel)
	{
		model = new char*[size[HEIGHT]];
		for (int count = 0; count < size[HEIGHT]; count ++)
		{
			model[count] = new char[size[WIDTH]];
			for (int count2 = 0; count2 < size[WIDTH]; count2++)
				model[count][count2] = extModel[count][count2];
		}
	}
};

extern StopWatch g_timer;
extern bool g_quitGame;
extern COORD shipLocation;
extern COORD consoleSize;
extern char ship[5][20];
extern size_t shipLen;
extern int bullets[80];
extern int score;
extern int Life;

void mainLoop();
void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory
void chooseShip(int);
void renderBullets();
bool createEnemy(enemies[], int, int, int, char** , int, int x = 80, int life = 1);
bool checkBulletCollision(enemies[], int);
bool checkBulletCollision(enemies&);
bool checkEnemyCollision(enemies[], int);
bool Levelcat(int);
bool Levelaste(int);
bool levelBoss(int);
void displayLevel(int);
bool checkClear(enemies[], int);
bool checkClear (enemies);

void initCat();
void createCat(int);
void moveCat(int);
void initAste();
void createAste(int);
void moveAste(int);
void initBoss(int);
void moveBoss();
void moveBossBullets(int);

bool initEnemies(char*, int);
bool initLevel(int);
void renderShip();
int spawnEnemy();
bool spawnEnemy(enemies&);
void renderEnemy(enemies[], int);
void renderEnemy(enemies&);
void moveEnemy(enemies[], int);
void moveEnemy(enemies&);
void moveEnemy(enemies&, int&, int&);

void Pause();
void gRestart();
void ChangeShip();
void DisplayOptions();
void DisplayMainMenu();
void DisplayInGame();
void Selection();
void GameOver();
int getKey(); //Get user input, not to be confused with the up down etc

void CurrentScore();
void LifeCounter();

#endif //_GAME_H
