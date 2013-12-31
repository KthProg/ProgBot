#ifndef _PROGBOT_DEF
#define _PROGBOT_DEF

#include "IRCBot.h"
#include <array>
#include <random>
#include <time.h>
#include "TicTacToe.h"
#include <sstream>

class ProgBot : public IRCBot
{
public:
	ProgBot(string port, string host):IRCBot(port, host)
	{
		gInt = 0;
		prefix = "P! ";
		login = "NICK Progger\nUSER  Progger 8 *  : Progger\r\n";

		split.push_back(":");	split.push_back("!");
		split.push_back("#");	split.push_back(":");
		split.push_back(prefix);split.push_back(" ");
		split.push_back("");	split.push_back("\n");

		items.push_back("user");
		items.push_back("room");
		items.push_back("cmd");
		items.push_back("input");
	}

	void doCmd();
	//void parseInput();

	void say();
	void ttt(); //tic tac toe
	TicTacToe tic;

	void gNum(); //guess a number
	int gInt;
};

#endif
