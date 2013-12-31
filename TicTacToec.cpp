#include "TicTacToe.h"

char TicTacToe::checkWinner()
{
	char winner = EMPTY;

	for(int i = 0; i <=2; ++i)
	{
		if(board.at(i) == board.at(i + 3) && board.at(i + 3) == board.at(i + 6))
		{
			if(board.at(i)!=EMPTY)
			{
				winner = board.at(i);
				break;
			}
		}
		if(board.at(3*i) == board.at(3*i + 1) && board.at(3*i + 1) == board.at(3*i + 2))
		{
			if(board.at(3*i)!=EMPTY)
			{
				winner = board.at(3*i);
				break;
			}
		}
	}
	if(board.at(2) == board.at(4) && board.at(4) == board.at(6))
	{
		if(board.at(2)!=EMPTY)
		{
			winner = board.at(2);
		}
	}
	if(board.at(0) == board.at(4) && board.at(4) == board.at(8))
	{
		if(board.at(0)!=EMPTY)
		{
			winner = board.at(0);
		}
	}

	return winner;
}

void TicTacToe::makeMove()
{

	char winner;

	srand(time(NULL));

	int rPos;
	do
	{
		rPos = rand()%9;
	}
	while(board.at(rPos) != EMPTY);

	board.at(rPos) = 'o';
}


/*
if(winner!=EMPTY)
	{
		switch(winner)
		{
			case 'x':
				writeSocket("PRIVMSG #" + pb.input["room"] + ":You win! =[" + "\r\n");
				break;
			case 'o':
				writeSocket("PRIVMSG #" + pb.input["room"] + ":I win! =]" + "\r\n");
				break;
		}
		board.fill(EMPTY);
	}
	*/
