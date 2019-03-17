#include "Client.hpp"

Client::Client(string ip, uint16_t port)
{
    if(inet_pton(AF_INET, ip.c_str(), &serverAddress.sin_addr) <= 0)
    {
        perror("IP Addresss in incorrect format.\n");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
}

Client::~Client()
{

}

void Client::BeginRead()
{

}

void Client::EndRead()
{

}

uint8_t Client::Send(string input)
{

}

void Client::Connect()
{
    struct sockaddr_in address;

    if( (this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Failure to create socket\n");
        exit(EXIT_FAILURE);
    }

    if(connect(this->sockfd, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr)) < 0)
    {
        perror("Failure to connect to server.\n");
        exit(EXIT_FAILURE);
    }
}

void Client::Disconnect()
{
    
}