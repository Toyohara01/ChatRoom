#include "Client.hpp"

Client::~Client()
{
    Disconnect(); 
}

string Client::Read()
{

    char buffer[BUFFER_SIZE];
    memset(buffer, '\0', BUFFER_SIZE);

    ssize_t bytesRead = recv(this->connectionID, buffer, BUFFER_SIZE, MSG_WAITALL); //do while; read until you get what you request 

    if(bytesRead <= 0)
    {
//        perror("Error on receiving packet");
  //      exit(EXIT_FAILURE);
    }

    string message(buffer);
    
    return buffer;
}

uint8_t Client::Send(string input)
{   
    ssize_t bytesSent = send(this->connectionID, input.c_str(), input.length(), 0);

    if(bytesSent <= 0)
    {
    //    perror("Error Receving Message");
      //  exit(EXIT_FAILURE);
    }
}

int Client::Connect(string ip, uint16_t port)
{
    struct sockaddr_in address;
    int newConnection = -1;

    if(inet_pton(AF_INET, ip.c_str(), &address.sin_addr) <= 0)
    {
        //perror("IP Addresss in incorrect format.\n");
        //exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if( (newConnection = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        //perror("Failure to create socket\n");
        //exit(EXIT_FAILURE);
    }

    if(connect(newConnection, (struct sockaddr *)&address, sizeof(struct sockaddr)) < 0)
    {
        //perror("Failure to connect to server.\n");
        //exit(EXIT_FAILURE);
    }

    this->connectionID = newConnection;

    return this->connectionID;
}

void Client::Disconnect()
{
    if(close(connectionID) < 0)
    {
        //perror("Error on closing socket");
        //exit(EXIT_FAILURE);
    }
}