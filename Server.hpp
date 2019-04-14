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

using namespace std;

//Constants 
#define BUFFER_SIZE 2048
#define CONNECTIONACCEPTANCERATE 1

class Server
{
private:
	int sockfd;
	string ipAddress;
	uint16_t port;
	int options;
	void (*messageProcessing)(string);

	int Accept(int sockID);
	int SetupSocket();
	void Bind(int sockID, string ip, uint16_t port);
	void Listen(int sockID);

public:
	int CreateSocket(int port);
	void Disconnect();
	void Disconnect(int sockID);
	void Send(int connection, string input);
	static void staticRead(int connectionID);
    Server(string ip, uint16_t port);
	string Read(int connectionID);
	int AcceptListeningSocket();
	int AcceptClientConnection(int sockID);
	void CreateListeningSocket();
    ~Server();
	
};

#endif

