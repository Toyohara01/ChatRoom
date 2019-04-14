#include "Server.hpp"

Server::Server(string ip, uint16_t port)
{ 
    this->ipAddress = ip;
    this->port = port;
}

Server::~Server()
{
    Disconnect();
}

int Server::SetupSocket()
{
    int newSocket;
    // Create socket
    if((newSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failure");
        exit(EXIT_FAILURE);
    }
    return newSocket;
}

void Server::CreateListeningSocket()
{
    int setOption = 1;

    this->sockfd = SetupSocket();

    //Allow socket to be re-used
    if(0 != setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &setOption, sizeof(int)))
    {
        perror("Failure to modify socket options\n");
        exit(EXIT_FAILURE);
    }

    Bind(this->sockfd, this->ipAddress, this->port);
    Listen(this->sockfd);
}

int Server::CreateSocket(int port)
{
    int newSock = -1;

    newSock = SetupSocket();
    Bind(newSock, this->ipAddress, port);
    Listen(newSock);

    return newSock;
}

void Server::Bind(int sockID,string ip, uint16_t port)
{
    struct sockaddr_in newConn;

    if(inet_pton(AF_INET, ip.c_str(), &newConn.sin_addr) <= 0)
    {
        perror("IP Addresss in incorrect format.\n");
        exit(EXIT_FAILURE);
    } 

    newConn.sin_family = AF_INET;
    newConn.sin_port = htons(port);

    int result = bind(sockID, (struct sockaddr *) &newConn, sizeof(struct sockaddr));
    if(result == -1)
    {
        perror("Error binding socket to port\n");
        exit(EXIT_FAILURE);
    }
}

void Server::Listen(int sockID)
{
    if(listen(sockID, CONNECTIONACCEPTANCERATE) < 0)
    {
        perror("Error making socket listen.");
        exit(EXIT_FAILURE);
    }
}

int Server::AcceptListeningSocket()
{
    return Accept(this->sockfd);
}

int Server::AcceptClientConnection(int sockID)
{
    return Accept(sockID);
}

int Server::Accept(int sockID)
{
    struct sockaddr_in incomingConnection;
    socklen_t clientSize = sizeof(sockaddr_in);
    int newConnection = -1;

    if((newConnection = accept(sockID, (struct sockaddr *)&incomingConnection, &clientSize)) < 0)
    {
        perror("Error accepting connection.");
        exit(EXIT_FAILURE);
    }

    return newConnection;
}

void Server::Disconnect()
{
    Disconnect(this->sockfd);
}

void Server::Disconnect(int sockID)
{
    if(close(sockID) < 0)
    {
        perror("Error on closing socket");
        exit(EXIT_FAILURE);
    }
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