#include "Client.hpp"

Client::Client(string IP, uint8_t port)
{
    this->IP = IP;
    this->port = port;
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
    struct sockaddr_in address, server_address;

    if( (this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Failure to create socket\n");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, '0', sizeof(sockaddr_in));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(this->port);

    char IPAddress[IP.length()];

    if(inet_pton(AF_INET, this->IP.c_str(), &server_address.sin_addr) <= 0)
    {
        perror("IP Addresss in incorrect format.\n");
        exit(EXIT_FAILURE);
    }

    if(connect(this->sockfd, (struct sockaddr *)&server_address, sizeof(struct sockaddr)) < 0)
    {
        perror("Failure to connect to server.\n");
        exit(EXIT_FAILURE);
    }
}

void Client::Disconnect()
{
    
}