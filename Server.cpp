#include "Server.hpp"

Server::Server(string ip, uint16_t port)
{
    if(inet_pton(AF_INET, ip.c_str(), &address.sin_addr) <= 0)
    {
        perror("IP Addresss in incorrect format.\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
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
    Accept();
}

void Server::Bind()
{
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

void Server::Accept()
{
    struct sockaddr_in incomingConnection;
    socklen_t clientSize = sizeof(sockaddr_in);

    if((this->newConnection = accept(this->sockfd, (struct sockaddr *)&incomingConnection, &clientSize)) < 0)
    {
        perror("Error accepting connection.");
        exit(EXIT_FAILURE);
    }
}

void Server::Disconnect()
{

}

void Server::Read(void (*MessageProcessing)(string))
{
    char buffer[BUFFER_SIZE];
    memset(buffer, '\0', BUFFER_SIZE);

    ssize_t bytesRead = read(this->newConnection, buffer, BUFFER_SIZE);

    if(bytesRead <= 0)
    {
        perror("Error on receiving packet");
        exit(EXIT_FAILURE);
    }

    string message(buffer);

    (*MessageProcessing)(buffer);
}

void Server::Send(string input)
{
    char messageBuffer[BUFFER_SIZE];
    strcpy(messageBuffer, input.c_str());

    ssize_t bytesSent = send(this->newConnection, messageBuffer, sizeof(messageBuffer), 0);

    if(bytesSent <= 0)
    {
        perror("Error sending packet");
        exit(EXIT_FAILURE);
    }
}