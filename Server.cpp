/**************************************************************************
 * Server.cpp
 *  File containing the functionality needed to create sockets, send and 
 *  receive data over a network.
 * 
 *  Author: Kevin Pereira
 *  Spring 2019
 *  Class: SE420 / SE 310
 * 
***************************************************************************/

#include "Server.hpp"

/**************************************************************************
 * 
 *  Default constructor for class. 
 * 
***************************************************************************/
Server::Server()
{
}

/**************************************************************************
 * 
 *  Constructor for Server class.
 * 
 *  Inputs:
 *      -> std::string ip: IP address for socket
 *      -> uint16_t port: Base port for server class
 * 
***************************************************************************/
Server::Server(std::string ip, uint16_t port)
{ 
    this->ipAddress = ip;
    this->port = port;
}

/**************************************************************************
 * 
 * Destructor
 * 
***************************************************************************/
Server::~Server()
{
}

/**************************************************************************
 * 
 * Create new socket. 
 * 
 * Outputs:
 *      -> ID of socket created.
 * 
***************************************************************************/
int Server::SetupSocket()
{
    int newSocket;

    // Create socket KAP
    if((newSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failure");
        exit(EXIT_FAILURE);
    }

    return newSocket;
}

/**************************************************************************
 * 
 * Bind socket to port.
 * 
 * Outputs:
 *      -> Return number of new port. 
 * 
***************************************************************************/
int Server::CreateListeningSocket()
{
    int setOption = 1; //True KAP

    this->sockID = SetupSocket();

    //Allow socket to be re-used KAP
    if(0 != setsockopt(this->sockID, SOL_SOCKET, SO_REUSEADDR, &setOption, sizeof(int)))
    {
        perror("Failure to modify socket options\n");
        exit(EXIT_FAILURE);
    }

    int newPort = Bind();
    Listen(this->sockID);

    return newPort;
}

/**************************************************************************
 * 
 * Assigns IP address and port and attempts to bind to socket to port
 * if unsuccessful function will find a port that will work
 * 
 * Outputs:
 *      -> new port number of socket bound on network stack.
 * 
***************************************************************************/
int Server::Bind()
{
    struct sockaddr_in newConn;

    //Assign ip address in format xxx.xxx.xxx.xxx KAP
    if(inet_pton(AF_INET, this->ipAddress.c_str(), &newConn.sin_addr) <= 0)
    {
        perror("IP Addresss in incorrect format.\n");
        exit(EXIT_FAILURE);
    } 

    //Assign new port KAP
    newConn.sin_family = AF_INET;
    newConn.sin_port = htons(this->port);

    //loop while bind is not successful KAP
    while(bind(sockID, (struct sockaddr *) &newConn, sizeof(struct sockaddr)) < 0)
    {   
        //change port and reassign KAP
        this->port+=1;
        newConn.sin_port = htons(this->port);
    }    

    return port;
}

/**************************************************************************
 * 
 * Tells the socket to begin listening for connections on the network stack.
 * 
 * Inputs: 
 *      -> sockID: socket file descriptor for socket to be placed on 
 *                 listening mode. 
 * 
***************************************************************************/
void Server::Listen(int sockID)
{
    // Listening is critical to program critical KAP
    if(listen(sockID, CONNECTIONACCEPTANCERATE) < 0)
    {
        perror("Error making socket listen.");
        exit(EXIT_FAILURE);
    }
}

/**************************************************************************
 * 
 * Accepts connection from connecting client.
 * 
 * Outputs: 
 *      -> New file descriptor for new connection
 * 
***************************************************************************/
int Server::Accept()
{
    struct sockaddr_in incomingConnection;
    socklen_t clientSize = sizeof(sockaddr_in);
    int newConnection = -1;

    //Accept connection if there is an error report it KAP
    if((newConnection = accept(this->sockID, (struct sockaddr *)&incomingConnection, &clientSize)) < 0)
    {
        perror("Error accepting connection.");
    }

    // Set class attribute with newly accepted connection KAP
    this->connectionID = newConnection;
    return newConnection;
}

/**************************************************************************
 * 
 * Close socket file descriptor for connected client.
 * 
***************************************************************************/
void Server::CloseConnection()
{
    //Close connection if error report it. KAP
    if(close(this->connectionID)< 0)
    {
        perror("Error on closing socket");
    }
}

/**************************************************************************
 * 
 * Close socket file descriptor for listening socket 
 * 
***************************************************************************/
void Server::Disconnect()
{
    //Close connection if error report it. KAP
    if(close(this->sockID) < 0)
    {
        perror("Error on closing socket");
    }
}

/**************************************************************************
 * 
 * Receives message from client over the network. 
 * 
 * Outputs: 
 *      -> message received 
 * 
***************************************************************************/
std::string Server::Read()
{
    while(true)
    {
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);

        //Insert a recursive reading until buffer is full. KAP
        ssize_t bytesRead = read(this->connectionID, buffer, BUFFER_SIZE);

        // Throw exception if zero bytes are read, connction interrupted begin
        // throw exception KAP
        if(bytesRead <= 0)
        {
            throw NetworkError();
        }

        std::string message(buffer);

        return message; 
    }
}

 /**************************************************************************
 * 
 * Sends message to client over the network. 
 * 
***************************************************************************/
void Server::Send(std::string input)
{
    static std::mutex mtx;
    char messageBuffer[BUFFER_SIZE];
    strcpy(messageBuffer, input.c_str());

    // Allow only one thread to send message at a time KAP
    mtx.lock();
    ssize_t bytesSent = send(this->connectionID, messageBuffer, sizeof(messageBuffer), 0);
    mtx.unlock();

    //If 0 bytes are sent then connection was interuptted during send 
    // throw exception KAP
    if(bytesSent <= 0)
    {
        throw NetworkError();
    }
}