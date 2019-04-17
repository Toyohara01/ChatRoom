#include "Server.hpp"

Server::Server()
{
    
}

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

int Server::CreateListeningSocket()
{
    int setOption = 1; //True

    this->sockID = SetupSocket();

    //Allow socket to be re-used
    if(0 != setsockopt(this->sockID, SOL_SOCKET, SO_REUSEADDR, &setOption, sizeof(int)))
    {
        perror("Failure to modify socket options\n");
        exit(EXIT_FAILURE);
    }

    int newPort = Bind();
    Listen(this->sockID);

    return newPort;
}

int Server::Bind()
{
    struct sockaddr_in newConn;

    if(inet_pton(AF_INET, this->ipAddress.c_str(), &newConn.sin_addr) <= 0)
    {
        perror("IP Addresss in incorrect format.\n");
        exit(EXIT_FAILURE);
    } 

    newConn.sin_family = AF_INET;
    newConn.sin_port = htons(this->port);

    while(bind(sockID, (struct sockaddr *) &newConn, sizeof(struct sockaddr)) < 0)
    {
        this->port+=1;
        newConn.sin_port = htons(this->port);
    }    

    return port;
}

void Server::Listen(int sockID)
{
    if(listen(sockID, CONNECTIONACCEPTANCERATE) < 0)
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

    if((newConnection = accept(this->sockID, (struct sockaddr *)&incomingConnection, &clientSize)) < 0)
    {
        perror("Error accepting connection.");
        exit(EXIT_FAILURE);
    }
    this->connectionID = newConnection;
    return newConnection;
}

void Server::CloseConnection()
{
    
    if(close(this->connectionID)< 0)
    {
        //perror("Error on closing socket");
    }
}

void Server::Disconnect()
{
    if(close(this->sockID) < 0)
    {
        perror("Error on closing socket");
        exit(EXIT_FAILURE);
    }
}

string Server::Read()
{
    while(true)
    {
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);

        //Insert a recursive reading until buffer is full. If it needs to be full. full of '\0'?
        ssize_t bytesRead = read(this->connectionID, buffer, BUFFER_SIZE);

        if(bytesRead <= 0)
        {
            perror("Error on receiving packet");
            //exit(EXIT_FAILURE);
        }

        string message(buffer);

        return message; 
    }
}
 
void Server::Send(string input)
{
    char messageBuffer[BUFFER_SIZE];
    strcpy(messageBuffer, input.c_str());

    //while loop that continues to send until all bytes in buffer are sent?  
    ssize_t bytesSent = send(this->connectionID, messageBuffer, sizeof(messageBuffer), 0);

    if(bytesSent <= 0)
    {
        perror("Error sending packet");
        exit(EXIT_FAILURE);
    }
}