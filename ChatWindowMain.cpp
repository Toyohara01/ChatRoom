#include "ChatWindow.hpp"

int main(int argc, char** argv)
{
    vector<class Message> messages;
    messages.clear();

    // Get IP Address and port of server to connect to. 
    string IPAddress = "127.0.0.1";
    uint16_t Port = 55500; //Hardcode for initial connection then reassign once connection is made 
   
    class ChatWindow window(IPAddress, Port);

    window.Login();
}