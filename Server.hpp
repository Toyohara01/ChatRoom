#ifndef SERVER_HPP
#define SERVER_HPP

#include "Enigma.hpp"
#include "Message.hpp"

#include <string>

using namespace std;

class Server
{
    private:
	int sockfd;
	int setsockopt;
	int bind;
	int listen;
	int new_socket;

	void SetupSocket();
	void Bind();
	void Listen();
	void Connect();
	void Disconnect();
	void BeginRead();
	void EndRead();

    public:
	uint8_t Send(string input);
    Server();
    ~Server();
};

#endif
