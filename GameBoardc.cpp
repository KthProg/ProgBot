#include "GameBoard.h"

void GameBoard::clear()
{
	for(char &i : board)
	{
		i = EMPTY;
	}
}

GameBoard::GameBoard(int w, int h)
{
	width = w;
	height = h;
	board.resize(w*h);
	clear();
}

ostream& operator<<(ostream &os, GameBoard &gb)
{
	for(int i = 0; i < gb.board.capacity(); ++i)
	{
		os << '|' << gb.board.at(i);
		if(((i+1)%gb.width) == 0)
		{
			os << '|' << endl;
		}
	}
	return os;
}

void GameBoard::chaPiece(int i, char c)
{
	if(board.at(i - 1) == EMPTY)
	{
		board.at(i - 1) = c;
	}
	else
	{
		state = "Position already filled.";
	}
}

void GameBoard::movPiece(int i, int j)
{
	if(board.at(j - 1) == EMPTY)
	{
		board.at(j - 1) = board.at(i - 1);
		board.at(i - 1) = EMPTY;
	}
	else
	{
		state = "Position already filled.";
	}
}

string GameBoard::getState()
{
	return state;
}
