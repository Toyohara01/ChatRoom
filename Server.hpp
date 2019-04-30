/**************************************************************************
 * 
 * Module that gives the hosting capabilities to a higher class.
 * Allows for sockets to be created and bounded to a port and allows
 * for connections to be established so that messages can be sent back 
 * and forth over a network. 
 * 
***************************************************************************/
#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream> 
#include <vector>
#include <string>
#include <cerrno>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <thread> 
#include <functional>
#include <mutex>

#include "Exception.hpp"

//Constants 
#define BUFFER_SIZE 2048
#define CONNECTIONACCEPTANCERATE 1

class Server
{
private:
	int sockID;
	int connectionID;
	std::string ipAddress;
	uint16_t port;

	int SetupSocket();
	int Bind();
	void Listen(int sockID);

public:

	Server();
    Server(std::string ip, uint16_t port);
	~Server();
	void Disconnect();
	void CloseConnection();
	void Send(std::string input);
	std::string Read();
	int CreateListeningSocket();
	int Accept();	
};

#endif

