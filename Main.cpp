#include "TetrisEngine.h"

/*
TODO============================================
- Colors/Sprites

- Menu???? (Hard?)
*/

int main()
{
	TetrisEngine myGame;
	myGame.ConstructConsole(26, 24, TetrisEngine::DEFAULT_BLOCK_SIZE_PIXEL, TetrisEngine::DEFAULT_BLOCK_SIZE_PIXEL);
	myGame.Start();

	return 0;
}