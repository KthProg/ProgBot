#include "IRCBot.h"
void IRCBot::doCmd()
{
	readSocket();
	cout << info;
	parseInput();

	if(input["cmd"] == "pong")
	{
		pong();
	}
}
void IRCBot::parseInput()
{
	if(info.substr(0,4) == "PING")
	{
		input["cmd"] = "pong";
		input["input"] = info.substr(6,string::npos);
	}
	else
	{
		try
		{
			for(int i = 0; i<items.size(); ++i)
			{
				int start = info.find(split[2*i], 0) + split[2*i].length();
				int strEnd = info.find(split[2*i + 1], start);
				input[items[i]] = info.substr(start, strEnd - start);
				info = info.substr(strEnd + 1, string::npos);
			}
		}
		catch(exception e)
		{
			cout << "Parse Error: " << e.what() << endl;
			input.clear();
		}
	}
}

void IRCBot::pong()
{
	writeSocket("PONG :" + input["input"]);
	writeSocket("JOIN #coffeesh0p\r\n");
}
