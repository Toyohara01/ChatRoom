#ifndef CHATWINDOW_HPP
#define CHATWINDOW_HPP

#include "Client.hpp"
#include "Message.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <thread>

using namespace std;

const string FUNCTION = "()";

class ChatWindow
{
private:
    string ip;
    uint16_t port;
    int sockID;
    Client client;
    bool continueSession;
    thread readMessagesThread;
    vector<thread> processMessagesThreadBuffer;

    void ProcessMessage(string input);
    void Disconnect();
    void Connect();
    void Chat();
    void readMessageHandler();
    void GarbageCollector();
    void StringInterpreter(string input);

public:
    ChatWindow(); //Empty constructor
    ChatWindow(string ip, uint16_t port);
    void Login();
    void Logout();
    

};

#endif //CHATWINDOW_HPP

