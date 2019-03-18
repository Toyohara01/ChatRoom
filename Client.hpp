#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Enigma.hpp"
//#include "User.hpp" //@@@ Do we need to create this header??

#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
//#include <netinet/in.h>

#include <iostream>
#include <string> 

using namespace std;

//Constants 
#define BUFFER_SIZE 2048


class Client
{
    private:
	struct sockaddr_in serverAddress;
	int sockfd;

	void BeginRead();
	

    public:
    Client(string IP, uint16_t port);
	~Client();
	uint8_t Send(string input);
	void Connect();
	void Read(void (*MessageProcessing)(string));
	void Disconnect();
};

#endif // CLIENT_HPP
