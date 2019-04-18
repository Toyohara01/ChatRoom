#ifndef CHATROOM_HPP
#define CHATROOM_HPP

#include "Server.hpp"

#include <iostream>
#include <thread>
#include <vector>
#include <iterator>
#include <chrono>
#include <mutex>

#define MAX_CONNECTIONS 10

using namespace std;

typedef struct User
{
    int connectionID;
    uint16_t port;
    string username;
    thread *messageListener;
    Server *connection;
    bool continueReading;

    User(); //empty constructor 

    User(int connectionID, uint16_t port, string username, Server *connection, thread *listener)
    {
        this->connectionID = connectionID;
        this->port = port;
        this->username = username;
        this->messageListener = listener;
        this->connection = connection;
        this->continueReading = true;
    }
}User;

class ChatRoom
{
private:
    vector<User> connections;
    Server server;
    bool continueListening;
    string IPAddress;
    uint16_t port;

    void RemoveFromChatroom(int connectionID);
    bool DoesUserExist(string name);
    vector<User>::iterator LocateUser(int connectionID);
    void FindPort();
    

public:
    ChatRoom(string IPAddress, uint16_t port);
    ~ChatRoom();
    void Startup(); 
    void ReadHandler(int connectionID);
    void Shutdown();
    void ListenForConnections();
    void Admit();
};

#endif //CHATROOM_HPP