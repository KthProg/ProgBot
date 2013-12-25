#include "ProgBot.h"

void ProgBot::doCmd()
{
	parseInput(readSocket());

	if(input["cmd"] == "pong")
	{
		pong();
	}
	else
	if(input["cmd"] == "say")
	{
		say();
	}
}

void ProgBot::parseInput(string cmd)
{
	try
	{
		cmd = cmd.substr(1, string::npos);
		input["nick"] = cmd.substr(0, cmd.find('!',0));
		cmd = cmd.substr(cmd.find('!',0) + 1,string::npos);
		input["room"] = cmd.substr(cmd.find('#',0), cmd.find(':',0) - cmd.find('#',0));
		cmd = cmd.substr(cmd.find(':',0) + 1,string::npos);
		input["cmd"] = cmd.substr(cmd.find('!',0) + 2, cmd.find(' ',cmd.find('!',0) + 2) - (cmd.find('!',0) + 2));
		cmd = cmd.substr(cmd.find(' ',cmd.find('!',0) + 2) + 1, string::npos);
		input["input"] = cmd;
	}
	catch(exception e)
	{
		cout << "Exception while parsing user input: " << e.what() << endl;
	}
}

void ProgBot::pong()
{
	writeSocket("PONG :" + input["input"] + "\n");
	writeSocket("JOIN #coffeesh0p\n");
}

void ProgBot::say()
{
	writeSocket("PRIVMSG " + input["room"] + ":" + input["input"] + "\n");
}

string ProgBot::login = "NICK ProgBot\nUSER  ProgBot 8 *  : Prog Bot\n";
string ProgBot::prefix = "!P";
