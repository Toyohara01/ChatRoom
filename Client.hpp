#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Enigma.hpp"
//#include "User.hpp" //@@@ Do we need to create this header??
#include <iostream>
#include <string> 

using namespace std;

class Client
{
    private:
	string IP;
	int port;
	int sockfd;
	int connect;

	void BeginRead();
	void EndRead();

    public:
    Client(string ip, uint8_t port);
	~Client();
	uint8_t Send(string input);
	void Connect();
	void Disconnect();
};

#endif // CLIENT_HPP
