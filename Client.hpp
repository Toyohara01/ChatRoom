#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Enigma.hpp"
#include "User.hpp"

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
    Client();
	~Client();
	uint8_t Send(string input);
	void Connect();
	void Disconnect()
};

#endif // CLIENT_HPP
