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

void ProgBot::ttt()
{

	stringstream ss;

	try
	{
		int pos = atoi(input["input"].c_str());
		tic.chaPiece(pos,'x');
	}
	catch(exception e)
	{
		cout << "Tic-tac-toe error: " << e.what() << endl;
	}

	switch(tic.checkWinner())
	{
	case 'x':
		writeSocket("PRIVMSG #" + input["room"] + ":" + "You win!" + "\r\n");
		tic.clear();
		return;
	case 'o':
		writeSocket("PRIVMSG #" + input["room"] + ":" + "I win!" + "\r\n");
		tic.clear();
		return;
	}

	char c[8];
	ss << tic;

	for(int i = 0; i < tic.width; ++i)
	{
		ss.read(c,ss.str().find('\n',0) + 1);
		writeSocket("PRIVMSG #" + input["room"] + ":" + c + "\r\n");
	}

	
	writeSocket("PRIVMSG #" + input["room"] + ":" + "My turn!" + "\r\n");
	tic.makeMove();
	ss << tic;

	for(int i = 0; i < tic.width; ++i)
	{
		ss.read(c,ss.str().find('\n',0) + 1);
		writeSocket("PRIVMSG #" + input["room"] + ":" + c + "\r\n");
	}

	switch(tic.checkWinner())
	{
	case 'x':
		writeSocket("PRIVMSG #" + input["room"] + ":" + "You win!" + "\r\n");
		tic.clear();
		return;
	case 'o':
		writeSocket("PRIVMSG #" + input["room"] + ":" + "I win!" + "\r\n");
		tic.clear();
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
