#include "Client.hpp"

/**************************************************************************
 * 
 * Class destructor forces active connection to disconnect.
 * 
***************************************************************************/
Client::~Client()
{
}

/**************************************************************************
 * 
 * Reads message pending from server.
 * 
 * Outputs: 
 *      -> message received
 * 
***************************************************************************/
std::string Client::Read()
{

    char buffer[BUFFER_SIZE];
    memset(buffer, '\0', BUFFER_SIZE);

    //Read message KAP
    ssize_t bytesRead = recv(this->connectionID, buffer, BUFFER_SIZE, MSG_WAITALL); //do while; read until you get what you request 

    //If 0 bytes are read throw exception KAP
    if(bytesRead <= 0)
    {
        throw NetworkError();
    }

    std::string message(buffer);
    
    return buffer;
}

/**************************************************************************
 * 
 * Sends message from input over the network. 
 * 
 * Inputs: 
 *      -> string input of message to send
 * 
 * Outputs:
 *      -> count of number of characters sent. 
 * 
***************************************************************************/
uint8_t Client::Send(std::string input)
{   
    ssize_t bytesSent = send(this->connectionID, input.c_str(), input.length(), 0);

    // If zero bytes are sent throw exception KAP
    if(bytesSent <= 0)
    {
        throw NetworkError();
    }
}

/**************************************************************************
 * 
 * Connects client to socket on server using ip address and port provided. 
 * 
 * Inputs:
 *      -> ip: ip address provided in string format of host
 *      -> port: unsigned number representing port which to connect to
 * 
 * Outputs:
 *      -> file descriptor of socket that is connected 
 * 
***************************************************************************/
int Client::Connect(std::string ip, uint16_t port)
{
    struct sockaddr_in address;
    int newConnection = -1;

    if(inet_pton(AF_INET, ip.c_str(), &address.sin_addr) <= 0)
    {
        std::string msg = "Address in incorrect format";
        throw std::runtime_error(msg);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if( (newConnection = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::string msg = "Unable to create socket";
        throw std::runtime_error(msg);
    }

    if(connect(newConnection, (struct sockaddr *)&address, sizeof(struct sockaddr)) < 0)
    {
        std::string msg = "Unable to connect to socket";
        throw std::runtime_error(msg);
    }

    this->connectionID = newConnection;

    return this->connectionID;
}

/**************************************************************************
 * 
 * Disconnects from connected socket.
 * 
***************************************************************************/
void Client::Disconnect()
{
    close(this->connectionID);
    
    //change connection to id to invalid value KAP
    this->connectionID = -1;
}