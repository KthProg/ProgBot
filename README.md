ProgBot
=======

IRC bot using WinSocks, C++
Used msdn examples for WinSock.

There's a basic wrapper class for WinSocks called TCPClient. I subclass this for any classes requiring a TCP connection. I subclassed it in this case as ProgBot. the ProgBot class is a basic IRC bot to which commands can be added easily. The input is parsed and stored into an input struct in ProgBot. parseInput is a pure virtual function declared in TCPClient so that different protocols input can be parsed differently.
