#ifndef CHATROOM_HPP
#define CHATROOM_HPP

#include "Server.hpp"

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

#define MAX_CONNECTIONS 10

using namespace std;

typedef struct User
{
    int listeningSocketID;
    int connectionID;
    uint16_t port;
    string username;
    thread *messageListener;

    User(); //empty constructor 

    User(int listeningSocketID, int connectionID, uint16_t port, string username, thread *messageListener)
    {
        this->listeningSocketID = listeningSocketID;
        this->connectionID = connectionID;
        this->port = port;
        this->username = username;
        this->messageListener = messageListener;
    }
}User;

class ChatRoom
{
private:
    vector<User> connections;
    vector<uint16_t> availablePorts;
    Server server;
    void Reject(int connectionID);
    void ReadHandler(int connectionID);
    bool continueListening;

public:
    ChatRoom(string IPAddress, uint16_t port);
    ~ChatRoom();
    void Startup();
    void Shutdown();
    void ListenForConnections();
    void Admit(uint16_t port);
};

#endif //CHATROOM_HPP