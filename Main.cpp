#include <iostream>
#include "Game.h"
using namespace std;

int main(int argc, char * argv[])
{
	Game game;

	bool success = game.Initialize();
	
	if ( true )
	{
		game.MainLoop();
	}
	
	game.ShutDown();
	return 0;
}