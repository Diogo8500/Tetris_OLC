#include "TetrisEngine.h"
#include "Test.h"

/*
TODO============================================
- Colors/Sprites

- Menu???? (Hard?)
*/

int main()
{
	Test_Piece_Solid();
	Test_Board_CanFit();

	TetrisEngine myGame;
	myGame.ConstructConsole(26, 24, TetrisEngine::DEFAULT_BLOCK_SIZE_PIXEL, TetrisEngine::DEFAULT_BLOCK_SIZE_PIXEL);
	myGame.Start();

	return 0;
}