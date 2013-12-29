#ifndef _IRCBOT_DEF
#define _IRCBOT_DEF

#include "TCPClient.h"
#include <vector>

class IRCBot : public TCPClient
{
public:
	IRCBot(string port, string host):TCPClient(port, host){}
	string login;
	string prefix;

	vector<string> split;
	vector<string> items;

	virtual void doCmd();
	void parseInput();
	void pong();
};

#endif
