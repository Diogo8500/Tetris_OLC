#pragma once
#include <cstdlib>
#include "Pieces.h"

class TetrisBoard
{
private:
	//DEFAULTS
	static constexpr int HEIGHT = 20;
	static constexpr int WIDTH = 10;

	unsigned short *boardArray;
	int bHeight, bWidth;

public:
	TetrisBoard() : TetrisBoard(HEIGHT, WIDTH) {};
	TetrisBoard(int height, int width);
	TetrisBoard(const TetrisBoard& tb);
	TetrisBoard operator=(const TetrisBoard& tb) { return TetrisBoard(tb); };
	~TetrisBoard() { delete[] boardArray; };

public:
	int Height() const { return bHeight; }
	int Width() const { return bWidth; }
	bool Solid(int x, int y) const;
	bool CanPieceFit(const Piece& p, int x, int y) const;
	bool IsLineCLear(int y) const;
	bool IsLineComplete(int y) const;
	void PlacePiece(const Piece& p, int x, int y);
	void ClearLine(int y);
	void SwapLine(int srcY, int destY);
	void ClearBoard();

private:
	int index(int x, int y) const { return y * bWidth + x; }




	
};

