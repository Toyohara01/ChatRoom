/**************************************************************************
 * 
 * Gives calling class capability of connecting to a hosting socket.
 * Will allow for messges to be sent back and forth over a network. 
 * 
***************************************************************************/
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <thread>

#include "Exception.hpp"

//Constants KAP
#define BUFFER_SIZE 2048
 
class Client
{
    private:	
	int connectionID;

    public:
	~Client();
	std::string Read();
	uint8_t Send(std::string input);
	int Connect(std::string ip, uint16_t port);
	void Disconnect();
};

#endif // CLIENT_HPP 
