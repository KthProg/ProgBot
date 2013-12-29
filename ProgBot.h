#ifndef _PROGBOT_DEF
#define _PROGBOT_DEF

#include "IRCBot.h"
#include <array>
#include <random>
#include <time.h>

class ProgBot : public IRCBot
{
public:
	ProgBot(string port, string host):IRCBot(port, host)
	{
		board.fill('e'); 
		gInt = 0;
		prefix = "P! ";
		login = "NICK ProgBot\nUSER  ProgBot 8 *  : Prog Bot\r\n";

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
	array<char, 9> board;
	void gNum(); //guess a number
	int gInt;
};

#endif
