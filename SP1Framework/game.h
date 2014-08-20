#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <string>
#include <vector>

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

struct enemies
{
	COORD location;
	int size[2];
	char** look;

	void set(int x, int y, int width, int height)
	{
		location.X = x;
		location.Y = y;
		size[0] = width;
		size[1] = height;
	}

	void setlook(char** l)
	{
		look = new char*[size[0]];
		for (int count = 0; count < size[0]; count++)
		{
			look[count] = new char[size[1]];
			strcpy(look[count], l[count]);
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
extern enemies enemyNum[10];
extern int score;
extern char** enemycat;

void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory
void chooseShip(int);
void renderShip();
void renderBullets();
void createEnemy(int, int, char**);
void createEnemy(char);
void renderEnemy();
void checkBulletCollision();
void initCat();

void Pause();
void ChangeShip();
void DisplayOptions();
void DisplayMainMenu();
void DisplayInGame();
int getKey(); //Get user input, not to be confused with the up down etc

void CurrentScore();

#endif //_GAME_H
