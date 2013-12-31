#ifndef _GBOARD_DEF_
#define _GBOARD_DEF_

#include <vector>
#include <iostream>

using namespace std;

class GameBoard
{
protected:
	string *currentPlayer;
	static const char EMPTY = ' ';
	string state;
public:
	virtual char checkWinner() = 0;

	virtual void makeMove() = 0;

	GameBoard(int w, int h);

	vector<char> board;

	void chaPiece(int i, char c);
	void movPiece(int i, int j);

	friend ostream& operator<<(ostream &os, GameBoard &gb);

	vector<string> players;
	string getState();

	void clear();

	int width, height;
};

#endif
