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

using namespace std;

//Constants 
#define BUFFER_SIZE 2048
#define CONNECTIONACCEPTANCERATE 1

class Server
{
private:
	int sockID;
	int connectionID;
	string ipAddress;
	uint16_t port;

	int SetupSocket();
	int Bind();
	void Listen(int sockID);

public:

	Server();
    Server(string ip, uint16_t port);
	~Server();
	void Disconnect();
	void CloseConnection();
	void Send(string input);
	string Read();
	int CreateListeningSocket();
	int Accept();	


};

#endif

