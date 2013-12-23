#ifndef _TCPCLIENT_DEF

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
//#include <map>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

struct userInput
{
	string nick;
	string room;
	struct userText
	{
		string cmd;
		string input;
	} uTxt;
};

class TCPClient
{
private:
	SOCKET TCPSock;
	userInput userIn;
	//map<string, void (TCPClient::*)()> fm;
public:
	static string login;
	static string prefix;
	TCPClient();
	TCPClient(string port, string host);
	~TCPClient();
	string readSocket();
	void writeSocket(string write);
	void TCPConnect(string port, string host);
	void TCPDisconnect();
	void doCmd();
	void getInput(string cmd);
	//void makeMap();
	void pong();
	void say();
};

#define _TCPCLIENT_DEF
#endif
