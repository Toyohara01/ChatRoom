#include "../../Server.hpp"
#include "../../Client.hpp"

#include <iostream>
#include <vector> 
#include <iterator> 


bool SocketSetupTest();
bool AcceptSocketConnections();



int main()
{
    std::cout<<"Beginning Server module tests"<<std::endl; 

    //Setup socket tests


    //Accept connections Test

}

bool SocketSetupTest()
{
    bool result = false;
    std::string ip = "127.0.0.1";
    uint16_t port = 55500;
    std::vector<Server> list;
    std::vector<Server>::iterator it;
    std::vector<int> ports; 

    std::cout<<"Creating sockets";

    list.push_back(Server(ip, port));



}