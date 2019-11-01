#include "TetrisEngine.h"

bool TetrisEngine::OnUserCreate()
{
	srand(time(NULL));
	currentPiece = Pieces::RandomPiece(rand());
	nextPiece = Pieces::RandomPiece(rand());
	heldPiece = Pieces::pBlank;
	
	currentPieceX = 5; //FOR TESTING
	currentPieceY = 0; //FOR TESTING
	currentPlayer = L"";
	
	return true;
}

bool TetrisEngine::OnUserUpdate(float fElapsedTime)
{
	StateUpdate(fElapsedTime);
	DrawRoutine();
	return true;
}

void TetrisEngine::DrawRoutine()
{
	DrawBackground();
	DrawBoard();
	DrawCurrentPiece();
	DrawNextPiece();
	DrawHeldPiece();
	DrawScore();
	DrawLevel();
}

void TetrisEngine::StateUpdate(float fElapsedTime)
{	
	//Check piece state after tick for collisions
	if (lastTickTimeDif >= 1.0f/(gravity + turbo)) 
	{
		if (!board.CanPieceFit(currentPiece, currentPieceX, currentPieceY + 1))
		{
			board.PlacePiece(currentPiece, currentPieceX, currentPieceY);
			int lastLinesCleared = ClearCompleteLines();
			linesCleared += lastLinesCleared;
			score += Score(level, lastLinesCleared);
			if (linesCleared >= 10)
			{
				linesCleared = 0;
				level++;
				gravity += 0.2f;
			}
			RefitBoard();
			Spawn(nextPiece, 5, 0);
			if (!board.CanPieceFit(currentPiece, currentPieceX, currentPieceY)) Restart();	
			nextPiece = Pieces::RandomPiece(rand());
			held = false;
		}else currentPieceY++;	
		lastTickTimeDif = 0.0f;
	}
	CheckUserInput();
	lastTickTimeDif += fElapsedTime;
	lastHMovementTime += fElapsedTime;
	lastRMovementTime += fElapsedTime;
}

void TetrisEngine::Restart()
{
	OnUserCreate();
	board.ClearBoard();
	score = 0, level = 1;
	linesCleared = 0;
	gravity = 1;
}

void TetrisEngine::Spawn(Piece p, int x, int y)
{
	currentPiece = p;
	//nextPiece = Pieces::RandomPiece();
	currentPieceX = x;
	currentPieceY = y;
}

void TetrisEngine::CheckUserInput()
{
	for (size_t k = 0; k < 6; k++)							  //R   L  U   D  Space Ctrl
		bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x26\x28\x20\x11"[k]))) != 0;
	
	if (bKey[0])
	{
		MovePieceRight();
	}else
	if (bKey[1])
	{
		MovePieceLeft();
	}else
	if (bKey[2])
	{
		RotatePiece();
	}else
	if (bKey[3])
	{
		turbo = 17;
	}else
	if (bKey[4])
	{
		HardDrop();
	}
	else
	if (bKey[5])
	{
		HoldPiece();
	}
	else
	{
		hardDroped = false;
		turbo = 0;
	}

}

void TetrisEngine::MovePieceRight()
{
	if (board.CanPieceFit(currentPiece, currentPieceX + 1, currentPieceY))
	{
		if (lastHMovementTime > 0.15f)
		{
			currentPieceX++;
			lastHMovementTime = 0;
		}
	}
}

void TetrisEngine::MovePieceLeft()
{
	if (board.CanPieceFit(currentPiece, currentPieceX - 1, currentPieceY))
	{
		if (lastHMovementTime > 0.15f)
		{
			currentPieceX--;
			lastHMovementTime = 0;
		}
	}
}

void TetrisEngine::RotatePiece()
{
	if (board.CanPieceFit(currentPiece.Rotate(Rotation::LEFT), currentPieceX, currentPieceY + 1))
	{
		if (lastRMovementTime > 0.15f) {
			currentPiece = currentPiece.Rotate(Rotation::LEFT);
			lastRMovementTime = 0.0f;
		}
	}
}

void TetrisEngine::HardDrop()
{
	if (!hardDroped) {   
		while (board.CanPieceFit(currentPiece, currentPieceX, currentPieceY + 1))
			currentPieceY++;
		lastTickTimeDif = 1;
		hardDroped = true;
	}
}

void TetrisEngine::HoldPiece()
{
	if (!held)
	{
		if (heldPiece == Pieces::pBlank)
		{
			heldPiece = currentPiece;
			Spawn(nextPiece, 5, 0);
			nextPiece = Pieces::RandomPiece(rand());
		}
		else
		{
			Piece aux = currentPiece;
			Spawn(heldPiece, 5, 0);
			heldPiece = aux;
		}
		held = true;
	}
}

int TetrisEngine::ClearCompleteLines()
{
	int nLinesCleared = 0;
	for (int y = 2; y < board.Height() - 2; y++)
		for (int x = 2; x < board.Width() - 2; x++)
			if (board.IsLineComplete(y))
			{
				board.ClearLine(y);
				nLinesCleared++;
			}
	return nLinesCleared;
}

void TetrisEngine::RefitBoard()
{
	for (int y = board.Height() - 3; y >= 2; y--)
		if (board.IsLineCLear(y))
			for (int auxLine = y - 1; auxLine >= 2; auxLine--)
				if (!board.IsLineCLear(auxLine))
				{
					board.SwapLine(y, auxLine);
					break;
				}	
}

int TetrisEngine::Score(int level, int nLines)
{
	switch (nLines)
	{
		case 1: return 40 * (level + 1);
		case 2: return 100 * (level + 1);
		case 3: return 300 * (level + 1);
		case 4: return 1200 * (level + 1);
		default: return 0;
	}
}

void TetrisEngine::DrawBackground()
{
	for (int y = 0; y < ScreenHeight(); y++)
		for (int x = 0; x < ScreenWidth(); x++)
			Draw(x, y, 0);
}

void TetrisEngine::DrawBoard()
{
	for (int y = 0; y < board.Height(); y++)
		for (int x = 0; x < board.Width(); x++)
			if (board.Solid(x, y)) DrawString(x, y, L"#");
}

void TetrisEngine::DrawCurrentPiece()
{
	for (int y = 0; y < 4; y++)	
		for (int x = 0; x < 4; x++)
			if (currentPiece.Solid(x, y)) Draw(currentPieceX + x, currentPieceY + y);
}

void TetrisEngine::DrawNextPiece()
{
	DrawStringAlpha(15, 2, L"Next Piece");
	for (int y = 3; y < 7; y++)	
		for (int x = board.Width() + 4; x < board.Width() + 8; x++)
			if (nextPiece.Solid(x - board.Width() - 4, y - 3)) Draw(x, y);
}

void TetrisEngine::DrawHeldPiece()
{
	DrawStringAlpha(15, 8, L"Hold");
	for (int y = 9; y < 13; y++)
		for (int x = board.Width() + 4; x < board.Width() + 8; x++)
			if (heldPiece.Solid(x - board.Width() - 4, y - 9)) Draw(x, y);
}

void TetrisEngine::DrawScore()
{
	DrawStringAlpha(16, 20, L"Score:");
	DrawStringAlpha(16, 21, to_wstring(score));
}

void TetrisEngine::DrawLevel()
{
	DrawStringAlpha(16, 17, L"Level:");
	DrawStringAlpha(16, 18, to_wstring(level));
}


