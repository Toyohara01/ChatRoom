#ifndef SERVER_HPP
#define SERVER_HPP

#include "Enigma.hpp"
#include "Message.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <iostream> 
#include <string>

using namespace std;

//Constants 
#define BUFFER_SIZE 2048
#define PORT 9090



class Server
{
    private:
	int sockfd;
	int options = 1;
	struct sockaddr_in address;
	
	int new_socket;

	void SetupSocket();
	void Bind();
	void Listen();
	void Connect();
	void Disconnect();
	void BeginRead();
	void EndRead();

    public:
	void CreateSocket();
	uint8_t Send(string input);
    Server(string ip, uint8_t port);
    ~Server();
};

#endif
