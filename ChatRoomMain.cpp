#include "ChatRoom.hpp"

#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char** argv)
{
    bool terminate = true;

    ChatRoom room("127.0.0.1", 55500);

    room.Startup();

    //launch thread to listen for connection concurrently. 
    thread listenForConnnectionThread(&ChatRoom::ListenForConnections, &room);


 
    while(terminate)
    {
        string input;
        getline(cin, input);

        if(input == "quit")
        {
          room.Shutdown();
          listenForConnnectionThread.join();
          terminate = false;
        }
    }
}
