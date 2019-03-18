#include "Server.hpp"
#include "Archive.hpp"

#include <iostream>


using namespace std;

int main(int argc, char** argv)
{
    Server server = Server("192.168.0.26", 55689);
    server.CreateSocket();

    server.Read();

    while(true);
    //Archive archive("hello.txt");
}