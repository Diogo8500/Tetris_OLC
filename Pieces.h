#pragma once
#include <cstdlib>

class Piece
{
private:
	unsigned short blockArray;

public:
	constexpr Piece() : blockArray() {};
	constexpr Piece(const Piece& p) : blockArray(p.blockArray) {};
	constexpr Piece(unsigned short shape) : blockArray(shape) {};
	Piece& operator=(const Piece& p) { blockArray = p.blockArray; return *this; }
	bool operator==(const Piece& p) { return blockArray == p.blockArray ? true : false; }

public:
	Piece Rotate(int (*Rotation)(int, int))
	{
		unsigned short toReturn = 0;
		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++)
				if(Solid(x, y)) toReturn |= ((unsigned short)0x8000 >> Rotation(x, y));
		return toReturn;
	}
	bool Solid(int x, int y) const
	{
		return (blockArray & ((unsigned short)0x8000 >> (y * 4 + x))) != 0 ? true : false;
	}
};

namespace Pieces
{
	static constexpr Piece MakePiece(unsigned short firstRow, unsigned short secondRow, unsigned short thirdRow, unsigned short fourthRow)
	{
		return (firstRow << 12) | (secondRow << 8) | (thirdRow << 4) | fourthRow;
	}
	static constexpr Piece pO = MakePiece(0b0000,
		0b0110,
		0b0110,
		0b0000);

	static constexpr Piece pI = MakePiece(0b0000,
		0b1111,
		0b0000,
		0b0000);

	static constexpr Piece pT = MakePiece(0b0000,
		0b0100,
		0b1110,
		0b0000);

	static constexpr Piece pL = MakePiece(0b0000,
		0b0010,
		0b1110,
		0b0000);

	static constexpr Piece pJ = MakePiece(0b0000,
		0b1000,
		0b1110,
		0b0000);

	static constexpr Piece pS = MakePiece(0b0000,
		0b0110,
		0b1100,
		0b0000);

	static constexpr Piece pZ = MakePiece(0b0000,
		0b1100,
		0b0110,
		0b0000);

	static constexpr Piece pBlank = MakePiece(0b0000,
		0b0000,
		0b0000,
		0b0000);

	static constexpr Piece RandomPiece(int rand)
	{
		int r = rand % 7;
		if (r == 0) return pO;
		if (r == 1) return pI;
		if (r == 2) return pT;
		if (r == 3) return pL;
		if (r == 4) return pJ;
		if (r == 5) return pS;
		else        return pZ;
	}
	
}

namespace Rotation
{
	static constexpr int LEFT(int x, int y) { return 3 - y + x * 4; }
	static constexpr int RIGHT(int x, int y) { return 12 + y - x * 4; }
}

