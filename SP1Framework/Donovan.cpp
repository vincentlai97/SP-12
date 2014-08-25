#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

void LifeCounter()
{
	gotoXY(60,0);
	colour(0x10A);
	for( int x = 0; x < Life ; x++)
		std::cout << char(3);
		
	if (Life==0)
	{
		GameOver();
	}
}