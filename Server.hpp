#ifndef SERVER_HPP
#define SERVER_HPP

#include "Enigma.hpp"

class Server
{
    private:
	int sockfd;
	int setsockopt;
	int bind;
	int listen;
	int new_socket;

    public:
    Server();
    ~Server();
};

#endif
