#ifndef _TTT_DEF_
#define _TTT_DEF_

#include "GameBoard.h"
#include <random>
#include <ctime>

class TicTacToe : public GameBoard
{
public:
	TicTacToe():GameBoard(3,3){}
	char checkWinner();
	void makeMove();
};

#endif
