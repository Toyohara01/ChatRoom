#ifndef CHATWINDOW_HPP
#define CHATWINDOW_HPP

#include "Client.hpp"
#include "Message.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <thread>

using namespace std;


class ChatWindow
{
private:
    string ip;
    uint16_t port;
    int sockID;
    Client client;
    bool continueSession;
    thread readMessagesThread;

    void ProcessMessage(string input);
    void Disconnect(int connectionID);
    void Connect();
    void Chat();
    void readMessageHandler();

public:
    ChatWindow(); //Empty constructor
    ChatWindow(string ip, uint16_t port);
    void Login();
    void Logout();
    void StringInterpreter(string input);

};

#endif //CHATWINDOW_HPP

