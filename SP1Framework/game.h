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
	bool dir;
	int life;

	void set(int x, int y, int width, int height, int l, int d = 1)
	{
		location.X = x;
		location.Y = y;
		size[0] = width;
		size[1] = height;
		life = l;
		dir = d;
	}

	void setlook(char** l)
	{
		look = new char*[size[1]];
		for (int count = 0; count < size[1]; count++)
		{
			look[count] = new char[size[0]];
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
extern int score;
extern char** enemycat;
extern enemies catArr[40];
extern enemies asteArr[60];
extern double level;
extern char** enemyaste;
extern enemies boss;
extern enemies bossBullets[100];
extern char** bossBullet;
extern int Life;

void mainLoop();
void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory
void chooseShip(int);
void renderShip();
void renderBullets();
bool createEnemy(enemies[], int, int, int, char** , int, int x = 80, int life = 1);
void renderEnemy(enemies[], int);
void renderEnemy(enemies&);
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
