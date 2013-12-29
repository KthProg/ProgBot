ProgBot
=======

IRC bot using WinSocks, C++
Used msdn examples for WinSock.

There's a basic wrapper class for WinSocks called TCPClient. I subclass this for any classes requiring a TCP connection. I subclassed it as IRCBot, then subclassed IRCBot as ProgBot. The ProgBot class is a basic IRC bot to which commands can be added easily. The input is parsed and stored into an input map (string to string) in ProgBot. parseInput is a pure virtual function declared in TCPClient so that different protocols input can be parsed differently.
