#include "Server.hpp"
#include "Archive.hpp"

#include <iostream>

#define PORT 9090

using namespace std;

int main(int argc, char** argv)
{
    Server server = Server("192.168.1.1", 9090);
    server.CreateSocket();


    while(true);
    //Archive archive("hello.txt");
}