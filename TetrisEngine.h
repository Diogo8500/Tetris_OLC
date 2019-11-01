#pragma once
#include <string>
#include "BaseEngineGL.h"
#include "Pieces.h"
#include "TetrisBoard.h"

class TetrisEngine :
	public BaseEngineGL
{
private:
	TetrisBoard board;
	Piece currentPiece, nextPiece, heldPiece;
	int currentPieceX = 0, currentPieceY = 0;
	int score = 0, level = 1;
	int turbo = 0;
	int linesCleared = 0;
	float gravity = 1;
	float lastTickTimeDif = 0.0f;
	float lastHMovementTime = 0.0f;
	float lastRMovementTime = 0.0f;
	wstring currentPlayer;
	bool hardDroped = false;
	bool held = false;
	short bKey[5] = {};

public:
	TetrisEngine() {};
	virtual ~TetrisEngine() {};

private:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	void DrawRoutine();
	void StateUpdate(float fElapsedTime);

	void Restart();
	void Spawn(Piece p, int x, int y);
	void CheckUserInput();
	void MovePieceRight();
	void MovePieceLeft();
	void RotatePiece();
	void HardDrop();
	void HoldPiece();
	int ClearCompleteLines();
	void RefitBoard();
	int Score(int level, int nLines);

	void DrawBackground();
	void DrawBoard();
	void DrawCurrentPiece();
	void DrawNextPiece();
	void DrawHeldPiece();
	void DrawScore();
	void DrawLevel();

public: //Defaults
	static constexpr int DEFAULT_BLOCK_SIZE_PIXEL = 30;
};

