//Mostly created using WinSock examples from msdn

#include "TCPClient.h"

TCPClient::TCPClient(string port, string host)
{
	TCPConnect(port, host);
}

TCPClient::TCPClient()
{
}

TCPClient::~TCPClient()
{
	TCPDisconnect();
}
void TCPClient::writeSocket(string writeStr)
{
	int res = send(TCPSock, writeStr.c_str(), writeStr.length(), 0);

	if (res == SOCKET_ERROR) {
		cout << "Write failed: " << WSAGetLastError() << endl;
		TCPDisconnect();
	}

	cout << writeStr;
}
void TCPClient::TCPConnect(string port, string host)
{
	// initiate use of WS2_32.dll.
	WSADATA wsaData;
	int res = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(res !=0)
	{
		cout << "Could not initiate WS2_32.dll" << endl;
	}
	// initialize address information
	struct addrinfo *result = NULL,
                *ptr = NULL,
                hints;

	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	res = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);

	if (res != 0) {
		cout << "getaddrinfo failed" << endl;
		WSACleanup();
	}

	TCPSock = INVALID_SOCKET;

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr=result;

	// Create a SOCKET for connecting to server
	TCPSock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	
	if (TCPSock == INVALID_SOCKET) {
		cout << "Could not create socket." << endl;
		freeaddrinfo(result);
		WSACleanup();
	}

	// Connect to server.
	res = connect(TCPSock, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (res == SOCKET_ERROR) {
		closesocket(TCPSock);
		TCPSock = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (TCPSock == INVALID_SOCKET) {
		cout << "Unable to connect to server!" << endl;
		WSACleanup();
	}


}
void TCPClient::TCPDisconnect()
{
	closesocket(TCPSock);
	WSACleanup();
}
void TCPClient::doCmd()
{
	//this->fm[userIn.uTxt.cmd];
	if(userIn.uTxt.cmd == "pong")
	{
		pong();
	}
	else
	if(userIn.uTxt.cmd == "say")
	{
		say();
	}
}

void TCPClient::getInput(string cmd)
{
	try
	{
		cmd = cmd.substr(1, string::npos);
		userIn.nick = cmd.substr(0, cmd.find('!',0));
		cmd = cmd.substr(cmd.find('!',0) + 1,string::npos);
		userIn.room = cmd.substr(cmd.find('#',0), cmd.find(':',0) - cmd.find('#',0));
		cmd = cmd.substr(cmd.find(':',0) + 1,string::npos);
		userIn.uTxt.cmd = cmd.substr(cmd.find('!',0) + 2, cmd.find(' ',cmd.find('!',0) + 2) - (cmd.find('!',0) + 2));
		cmd = cmd.substr(cmd.find(' ',cmd.find('!',0) + 2) + 1, string::npos);
		userIn.uTxt.input = cmd;
	}
	catch(exception e)
	{
		cout << "Exception while parsing user input: " << e.what() << endl;
	}
}

string TCPClient::readSocket()
{
	const int BUFF_SIZE = 512;

	string result;
	char recvbuf[BUFF_SIZE];
	int res;
	// Receive data until all current data is recieved (buffer is not full)
	do {
		res = recv(TCPSock, recvbuf, BUFF_SIZE, 0);
		if (res > 0)
		{
			for(int i = 0; i<res; ++i)
			{
				result += recvbuf[i];
			}
		}
		else if (res == 0)
		{
			cout << "Connection closed" << endl;
		}
		else
		{
			cout << "Receive failed: " << WSAGetLastError() << endl;
		}
	} while (res == BUFF_SIZE);

	cout << result;
	if(result.substr(0,4) != "PING")
	{
		if(result.find('!',0) != string::npos)
		{
			getInput(result);
		}
	}
	else
	{
		userIn.uTxt.cmd = "pong";
		userIn.uTxt.input = result.substr(result.find(':',0) + 1,string::npos);
	}
	doCmd();

	return result;
}

/*void TCPClient::makeMap()
{
	fm["say"] = &TCPClient::say;
	fm["pong"] = &TCPClient::pong;
}*/

void TCPClient::pong()
{
	writeSocket("PONG :" + userIn.uTxt.input + "\n");
	writeSocket("JOIN #coffeesh0p\n");
}

void TCPClient::say()
{
	writeSocket("PRIVMSG " + userIn.room + ":" + userIn.uTxt.input + "\n");
}

string TCPClient::login = "NICK ProgBot\nUSER  ProgBot 8 *  : Prog Bot\n";
string TCPClient::prefix = "!P";
