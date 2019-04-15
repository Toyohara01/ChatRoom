#ifndef CHATROOM_HPP
#define CHATROOM_HPP

#include "Server.hpp"

#include <iostream>
#include <thread>
#include <vector>
#include <iterator>
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
    bool continueReading;

    User(); //empty constructor 

    User(int listeningSocketID, int connectionID, uint16_t port, string username, thread *messageListener)
    {
        this->listeningSocketID = listeningSocketID;
        this->connectionID = connectionID;
        this->port = port;
        this->username = username;
        this->messageListener = messageListener;
        this->continueReading = true;
    }
}User;

class ChatRoom
{
private:
    vector<User> connections;
    vector<uint16_t> availablePorts;
    Server server;
    bool continueListening;
    thread admitNewUser;

    void Reject(int connectionID);
    void ReadHandler(int connectionID);
    void RemoveFromChatroom(int connectionID);
    bool DoesUserExist(string name);
    vector<User>::iterator LocateUser(int connectionID);
    

public:
    ChatRoom(string IPAddress, uint16_t port);
    ~ChatRoom();
    void Startup();
    void Shutdown();
    void ListenForConnections();
    void Admit(uint16_t port);
};

#endif //CHATROOM_HPP