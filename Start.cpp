#include "ProgBot.h"

int main()
{
	ProgBot prog("6667", "irc.hackthissite.org");
	prog.readSocket();
	cout << prog;
	prog.writeSocket(prog.login);
	prog.readSocket();
	cout << prog;

	while(true)
	{
		try
		{
			prog.doCmd();
		}
		catch(exception e)
		{
			cout << "Uncaught exception: " << e.what() << endl;
		}
	}
	return 0;
}
