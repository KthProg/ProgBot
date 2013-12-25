#ifndef _TCPCLIENT_DEF
#define _TCPCLIENT_DEF

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <map>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;



class TCPClient
{
protected:
	SOCKET TCPSock;
	map <string, string> input;
public:
	TCPClient(string port, string host);
	~TCPClient();
	string readSocket();
	void writeSocket(string write);
	void TCPConnect(string port, string host);
	void TCPDisconnect();
	virtual void doCmd();
	virtual void parseInput(string cmd);
};

#endif
