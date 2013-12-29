#include "ProgBot.h"

void ProgBot::doCmd()
{
	
	IRCBot::doCmd();

	if(input["cmd"] == "say")
	{
		say();
	}
	else
	if(input["cmd"] == "ttt")
	{
		ttt();
	}
	else
	if(input["cmd"] == "gnum")
	{
		gNum();
	}
}

void ProgBot::say()
{
	writeSocket("PRIVMSG #" + input["room"] + ":" + input["input"] + "\r\n");
}

char checkWinner(array<char,9> *board, ProgBot* pb)
{
	char winner = 'e';

	for(int i = 0; i <=2; ++i)
	{
		if(board->at(i) == board->at(i + 3) && board->at(i + 3) == board->at(i + 6))
		{
			if(board->at(i)!='e')
			{
				winner = board->at(i);
				break;
			}
		}
		if(board->at(3*i) == board->at(3*i + 1) && board->at(3*i + 1) == board->at(3*i + 2))
		{
			if(board->at(3*i)!='e')
			{
				winner = board->at(3*i);
				break;
			}
		}
	}
	if(board->at(2) == board->at(4) && board->at(4) == board->at(6))
	{
		if(board->at(2)!='e')
		{
			winner = board->at(2);
		}
	}
	if(board->at(0) == board->at(4) && board->at(4) == board->at(8))
	{
		if(board->at(0)!='e')
		{
			winner = board->at(0);
		}
	}

	if(winner!='e')
	{
		switch(winner)
		{
			case 'x':
				pb->writeSocket("PRIVMSG #" + pb->input["room"] + ":You win! =[" + "\r\n");
				break;
			case 'o':
				pb->writeSocket("PRIVMSG #" + pb->input["room"] + ":I win! =]" + "\r\n");
				break;
		}
		board->fill('e');
	}

	return winner;
}

void ProgBot::ttt()
{
	srand(time(NULL));

	try
	{
		int pos = atoi(input["input"].c_str());
		if(board.at(pos - 1) == 'e')
		{
			board.at(pos - 1) = 'x';
		}
		else
		{
			writeSocket("PRIVMSG #" + ':' + input["room"] + ":Position already filled!" + "\r\n");
			return;
		}
	}
	catch(exception e)
	{
		cout << "Tic-tac-toe error: " << e.what() << endl;
	}

	writeSocket("PRIVMSG #" + input["room"] + ":" + board[0] + "|" + board[1] + "|" + board[2] + "\r\n");
	writeSocket("PRIVMSG #" + input["room"] + ":" + board[3] + "|" + board[4] + "|" + board[5] + "\r\n");
	writeSocket("PRIVMSG #" + input["room"] + ":" + board[6] + "|" + board[7] + "|" + board[8] + "\r\n");

	char winner = checkWinner(&board, this);
	if(winner!='e')
	{
		return;
	}

	writeSocket("PRIVMSG #" + input["room"] + ":My turn!" + "\r\n");

	int rPos;
	do
	{
		rPos = rand()%9;
	}
	while(board.at(rPos) != 'e');

	board.at(rPos) = 'o';

	writeSocket("PRIVMSG #" + input["room"] + ":" + board.at(0) + "|" + board.at(1) + "|" + board.at(2) + "\r\n");
	writeSocket("PRIVMSG #" + input["room"] + ":" + board.at(3) + "|" + board.at(4) + "|" + board.at(5) + "\r\n");
	writeSocket("PRIVMSG #" + input["room"] + ":" + board.at(6) + "|" + board.at(7) + "|" + board.at(8) + "\r\n");

	winner = checkWinner(&board, this);
	if(winner!='e')
	{
		return;
	}
}

void ProgBot::gNum()
{
	srand(time(NULL));

	if(gInt == 0) { gInt = rand()%21 + 1; }

	try
	{
		int guess = atoi(input["input"].c_str());
		if(guess == gInt)
		{
			writeSocket("PRIVMSG #" + input["room"] + ":You Win!" + "\r\n");
			gInt = 0;
			return;
		}
		else
		if(guess < gInt)
		{
			writeSocket("PRIVMSG #" + input["room"] + ":Higher!" + "\r\n");
		}
		else
		if(guess > gInt)
		{
			writeSocket("PRIVMSG #" + input["room"] + ":Lower!" + "\r\n");
		}
	}
	catch(exception e)
	{
		cout << "Guess a number error: " << e.what() << endl;
	}

	writeSocket("PRIVMSG #" + input["room"] + ":Guess a number from 1 to 21" + "\r\n");
}
