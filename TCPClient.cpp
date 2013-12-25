#include "TCPClient.h"

TCPClient::TCPClient(string port, string host)
{
	TCPConnect(port, host);
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

	// Should really try the next address returned by getaddrinfo
	// if the connect call failed

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

	return result;
}
