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

void Client::BeginRead(void (*MessageProcessing)(string))
{
     streamReader = thread([=] { Read(*MessageProcessing); } );
}


void Client::Read(void (*MessageProcessing)(string))
{
    while(true)
    {
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);

        ssize_t bytesRead = read(this->sockfd, buffer, BUFFER_SIZE);

        if(bytesRead <= 0)
        {
            perror("Error on receiving packet");
            exit(EXIT_FAILURE);
        }

        string message(buffer);
        
        (*MessageProcessing)(buffer);
    }
}

uint8_t Client::Send(string input)
{   
    ssize_t bytesSent = send(this->sockfd, input.c_str(), input.length(), 0);

    if(bytesSent <= 0)
    {
        perror("Error Receving Message");
        exit(EXIT_FAILURE);
    }
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