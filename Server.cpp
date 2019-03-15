#include "Server.hpp"

Server::Server(string ip, uint8_t port)
{

}

Server::~Server()
{

}

void Server::SetupSocket()
{
    if((this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket failure\n");
        exit(EXIT_FAILURE);
    }
}

void Server::CreateSocket()
{
    SetupSocket();
    Bind();
    Listen();
}

void Server::Bind()
{
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    
    if( bind(this->sockfd, (struct sockaddr *) &address, sizeof(struct sockaddr)) == -1) 
    {
        perror("Error binding socket to port\n");
        exit(EXIT_FAILURE);
    }
}

void Server::Listen()
{
    if(listen(sockfd, 10) < 0)
    {
        perror("Error making socket listen.");
        exit(EXIT_FAILURE);
    }
}

void Server::Connect()
{

}

void Server::Disconnect()
{

}

void Server::BeginRead()
{

}

void Server::EndRead()
{

}

uint8_t Server::Send(string input)
{
    uint8_t bytesRead = 0;

    return bytesRead;
}