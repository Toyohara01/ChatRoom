#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Enigma.hpp"
#include "User.hpp"

class Client
{
    private:
	string IP;
	int port;
	int sockfd;
	int connect;

    public:
    Client();
	Send();
	Receive();
	Connect();
	Disconnect()'
    ~Client();
};

#endif // CLIENT_HPP
