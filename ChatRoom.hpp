#ifndef CHATROOM_HPP
#define CHATROOM_HPP

#include "Server.hpp"

#include <iostream>
#include <thread>
#include <vector>

#define MAX_CONNECTIONS 10

using namespace std;

typedef struct User
{
    int socketID;
    string username;
    thread *messageListener;

    User(int socketID, string username, thread *messageListener)
    {
        this->socketID = socketID;
        this->username = username;
        this->messageListener = messageListener;
    }
}User;

class ChatRoom
{
private:
    vector<User> connections;
    Server server;
    void Reject(int connectionID);
    void ReadHandler(int connectionID);

public:
    ChatRoom();
    ~ChatRoom();
    void Startup();
    void Shutdown();
    void ListenForConnections();
    void Admit();
};

#endif //CHATROOM_HPP