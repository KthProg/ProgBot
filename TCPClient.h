#ifndef _TCPCLIENT_DEF
#define _TCPCLIENT_DEF

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <exception>

//#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class TCPClient
{
public:
	string info; // basically the buffer
	SOCKET TCPSock;
	map <string, string> input;

	TCPClient(string port, string host);
	~TCPClient();
	void readSocket();
	void writeSocket(string write);
	void TCPConnect(string port, string host);
	void TCPDisconnect();
	virtual void doCmd() = 0;
	virtual void parseInput() = 0;
	friend ostream& operator<<(ostream& os, TCPClient& tcp);
};

#endif
