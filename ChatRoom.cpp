#include "Server.hpp"
#include "Archive.hpp"

#include <iostream>


using namespace std;

void ProcessMessage(string input);

int main(int argc, char** argv)
{
    Server server = Server("172.30.170.250", 55689);
    server.CreateSocket();

    while(true)
    {
        string input;
        getline(cin, input);
        server.Send(input);
        server.Read(ProcessMessage);
    }
    //Archive archive("hello.txt");
}

void ProcessMessage(string input)
{
    cout<<input<<endl;
}

void EndRead()
{
    string temp; // string returned frm Client.EndRead();
    //Call Client.EndRead(); Clear calling flag. 

    class Message newMessage(temp, Receive);

    //launch new thread to process packet. 
}