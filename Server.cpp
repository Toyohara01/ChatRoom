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
}

void Server::Bind()
{
    int result = bind(this->sockfd, (struct sockaddr *) &address, sizeof(struct sockaddr));
    if(result == -1)
    {
        perror("Error binding socket to port\n");
        exit(EXIT_FAILURE);
    }
}

void Server::Listen()
{
    if(listen(this->sockfd, CONNECTIONACCEPTANCERATE) < 0)
    {
        perror("Error making socket listen.");
        exit(EXIT_FAILURE);
    }
}

int Server::Accept()
{
    struct sockaddr_in incomingConnection;
    socklen_t clientSize = sizeof(sockaddr_in);
    int newConnection = -1;

    if((newConnection = accept(this->sockfd, (struct sockaddr *)&incomingConnection, &clientSize)) < 0)
    {
        perror("Error accepting connection.");
        exit(EXIT_FAILURE);
    }

    return newConnection;
}

void Server::Disconnect()
{

}

string Server::Read(int connection)
{
    while(true)
    {
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);

        //Insert a recursive reading until buffer is full. If it needs to be full. full of '\0'?
        ssize_t bytesRead = read(connection, buffer, BUFFER_SIZE);

        if(bytesRead <= 0)
        {
            perror("Error on receiving packet");
            exit(EXIT_FAILURE);
        }

        string message(buffer);

        return message; 
    }
}
 
void Server::Send(int connection, string input)
{
    char messageBuffer[BUFFER_SIZE];
    strcpy(messageBuffer, input.c_str());

    //while loop that continues to send until all bytes in buffer are sent?  
    ssize_t bytesSent = send(connection, messageBuffer, sizeof(messageBuffer), 0);

    if(bytesSent <= 0)
    {
        perror("Error sending packet");
        exit(EXIT_FAILURE);
    }
}