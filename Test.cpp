#include "Test.h"
#include "Pieces.h"
#include "TetrisBoard.h"
#include <cassert>

void Test_Piece_Solid()
{
	Piece p = Pieces::pO;
	assert(!p.Solid(0, 0));
	assert(!p.Solid(1, 0));
	assert(!p.Solid(2, 0));
	assert(!p.Solid(3, 0));
	assert(!p.Solid(0, 1));
	assert(p.Solid(1, 1));
	assert(p.Solid(2, 1));
	assert(!p.Solid(3, 1));
	assert(!p.Solid(0, 2));
	assert(p.Solid(1, 2));
	assert(p.Solid(2, 2));
	assert(!p.Solid(3, 2));
	assert(!p.Solid(0, 3));
	assert(!p.Solid(1, 3));
	assert(!p.Solid(2, 3));
	assert(!p.Solid(3, 3));
}

void Test_Board_CanFit()
{
	TetrisBoard b;
	Piece p = Pieces::pO;

	assert(!b.CanPieceFit(p,0,0));
	assert(b.CanPieceFit(p, 1, 0));
	assert(b.CanPieceFit(p, 1, b.Height() - 2 - 4));
	assert(b.CanPieceFit(p, 1, b.Height() - 2 - 3));
	

}
