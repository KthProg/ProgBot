#include "TCPClient.h"

int main()
{
	TCPClient tcpc("6667", "irc.hackthissite.org");
	tcpc.readSocket();
	tcpc.writeSocket(tcpc.login);
	tcpc.readSocket();
	string recieved = "";

	while(true)
	{
		try
		{
			recieved = tcpc.readSocket();
		}
		catch(exception e)
		{
			cout << "Uncaught exception: " << e.what() << endl;
		}
	}
	return 0;
}
