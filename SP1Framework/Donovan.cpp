#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

void LifeCounter()
{
	gotoXY(60,0);
	colour(0x10A);
	std::cout << "Life: ";
	std::cout<< Life << std::endl;
}