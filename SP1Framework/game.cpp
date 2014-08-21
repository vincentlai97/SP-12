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
enemies enemyNum[10];
int score;
char** enemycat;
char** enemyaste;
enemies catArr[40];
enemies asteArr[60];
double level;
char** boss1;
enemies boss;
enemies bossBullets[100];
char** bossBullet;

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

	for (int count = 0; count < 10; count++)
	{
		enemyNum[count].size[0] = 0;
		enemyNum[count].size[1] = 0;
	}

	initCat();
	initAste();

	level = 1.1;

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
		bulletBuffer += 2;
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

	if (level == 1.1)
	{
		if (Levelcat (static_cast<int>(level))) level = 1.2;
		displayLevel(static_cast<int>(level));
		CurrentScore();
 	}
	if (level == 1.2)
	{
  		if (Levelaste (static_cast<int>(level))) level = 1.3;
		displayLevel(static_cast<int>(level));
		CurrentScore();
	}
	/*if (level == 1.1)
	{
		initBoss(1);
		if (levelBoss(static_cast<int>(level))) level = 2.1;
		displayLevel(static_cast<int>(level));
		CurrentScore();
	}*/
}
