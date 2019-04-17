#ifndef CLIENT_HPP
#define CLIENT_HPP

//#include "Enigma.hpp"
//#include "User.hpp" //@@@ Do we need to create this header??

#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>
//#include <netinet/in.h>

#include <iostream>
#include <string>
//#include <cerrno>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <thread>

using namespace std;

//Constants 
#define BUFFER_SIZE 2048
 
 //broken pipe handler 

class Client
{
    private:	
	int connectionID;
	FILE* readStream;
	FILE* writeStream;

    public:
	~Client();
	string Read();
	uint8_t Send(string input);
	int Connect(string ip, uint16_t port);
	void Disconnect();
};

#endif // CLIENT_HPP
