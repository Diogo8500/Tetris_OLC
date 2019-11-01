#include <cstring>
#include "TetrisBoard.h"

TetrisBoard::TetrisBoard(int height, int width)
{
	if (height < 4 || width < 4) throw - 1;
	boardArray = new unsigned short[(height + 4) * (width + 4)];
	bHeight = height + 4;
	bWidth = width + 4;
	for (int y = 0; y < bHeight; y++)
		for (int x = 0; x < bWidth; x++)
			(x == 0 || x == 1 || x == (bWidth - 1) || x == (bWidth - 2) || y == (bHeight - 1) || y == (bHeight - 2))
				? boardArray[index(x, y)] = 1 
				: boardArray[index(x, y)] = 0;
}

TetrisBoard::TetrisBoard(const TetrisBoard& tb)
{
	boardArray = new unsigned short[tb.bHeight * tb.bWidth];
	memmove(boardArray, tb.boardArray, (tb.bHeight * tb.bWidth) * sizeof(unsigned short));
	bHeight = tb.bHeight;
	bWidth = tb.bWidth;
}

bool TetrisBoard::Solid(int x, int y) const
{
	return boardArray[index(x, y)] != 0 ? true : false;
}

bool TetrisBoard::CanPieceFit(const Piece& p, int x, int y) const
{
	for (int _y = 0; _y < 4; _y++)
		for (int _x = 0; _x < 4; _x++)
			if(Solid(x + _x, y + _y) && p.Solid(_x, _y)) return false;
	return true;
}

bool TetrisBoard::IsLineCLear(int y) const
{
	for (int x = 2; x < bWidth - 2; x++)
		if (Solid(x, y)) return false;
	return true;
}

bool TetrisBoard::IsLineComplete(int y) const
{
	for (int x = 2; x < bWidth - 2; x++)
		if (!Solid(x, y)) return false;
	return true;
}

void TetrisBoard::PlacePiece(const Piece& p, int x, int y)
{
	for (int _y = 0; _y < 4; _y++)
	{
		for (int _x = 0; _x < 4; _x++)
		{
			if(p.Solid(_x, _y)) boardArray[index(x + _x, y + _y)] = (unsigned short)1;
		}
	}
}

void TetrisBoard::ClearLine(int y)
{
	for (int x = 2; x < bWidth - 2; x++)
		boardArray[index(x, y)] = (unsigned short)0;
}

void TetrisBoard::SwapLine(int srcY, int destY)
{
	unsigned short* auxLine = new unsigned short[bWidth - 4];
	memmove(auxLine, boardArray + index(2, srcY), (bWidth - 4) * sizeof(unsigned short));
	memmove(boardArray + index(2, srcY), boardArray + index(2, destY), (bWidth - 4) * sizeof(unsigned short));
	memmove(boardArray + index(2, destY), auxLine, (bWidth - 4) * sizeof(unsigned short));
	delete[] auxLine;
}

void TetrisBoard::ClearBoard()
{
	for (int y = 0; y < bHeight; y++)
		for (int x = 0; x < bWidth; x++)
			(x == 0 || x == 1 || x == (bWidth - 1) || x == (bWidth - 2) || y == (bHeight - 1) || y == (bHeight - 2))
			? boardArray[index(x, y)] = 1
			: boardArray[index(x, y)] = 0;
}
