#ifndef SERVER_HPP
#define SERVER_HPP

//#include "Enigma.hpp"
#include "Message.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
//#include <netinet/in.h>
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

using namespace std;

//Constants 
#define BUFFER_SIZE 2048
#define CONNECTIONACCEPTANCERATE 1

class Server
{
private:
	int sockfd;
	int options;
	struct sockaddr_in address;
	void (*messageProcessing)(string);

	void SetupSocket();
	void Bind();
	void Listen();
	void Disconnect();

public:
	void CreateSocket();
	void Send(int connection, string input);
	static void staticRead(int connectionID);
    Server(string ip, uint16_t port);
	string Read(int connectionID);
	int Accept();
	
    ~Server();
};

#endif

