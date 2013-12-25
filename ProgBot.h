#ifndef _PROGBOT_DEF
#define _PROGBOT_DEF

#include "TCPClient.h"

class ProgBot : public TCPClient
{
public:
	ProgBot(string port, string host):TCPClient(port, host){};
	static string login;
	static string prefix;
	void doCmd();
	void parseInput(string cmd);
	void pong();
	void say();
};

#endif
