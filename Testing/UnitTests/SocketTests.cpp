#include "../../Server.hpp"
#include "../../Client.hpp"

#include <iostream>
#include <vector> 
#include <stack> 
#include <iterator> 
#include <thread>
#include <chrono>

std::string messages[] = {"Hello world", "World Hello"};
bool sendMessageFlag = false;

bool SocketSetupTest();
bool AcceptSocketConnections();
void ClientConnectToServer(std::vector<int> ports);

int main()
{
    std::cout<<"Beginning Server module tests"<<std::endl; 

    //Setup socket tests
    bool socketSetupResult = SocketSetupTest();

    //Accept connections Test
    bool AccecptConnectionResult = AcceptSocketConnections();
}

bool SocketSetupTest()
{
    bool result = false;
    std::string ip = "127.0.0.1";
    uint16_t port = 55500;
    Server list[10];
    std::vector<int> ports; 

    std::cout<<"Creating sockets"<<std::endl;

    for(int index = 0; index < 10; index++)
    {
        list[index] = Server(ip, port);
        ports.push_back(list[index].CreateListeningSocket());
    }

    std::cout<<"On address 127.0.0.1 launch terminal and run"<<std::endl;
    std::cout<<"Mac: lsof -i"<<std::endl<<"Raspbian: netstat -natp"<<std::endl;
    std::cout<<"Linux: netstat -A inet -p"<<std::endl;
    std::cout<<"Makes sure the following ports are use:"<<std::endl;
    
    for(std::vector<int>::iterator index = ports.begin(); index < ports.end(); index++)
    {
        std::cout<<(*index)<<std::endl;
    }

    std::cout<<"Are these ports in use? Y/N: ";

    char input = getchar();

    if(input == 'Y' || input == 'y')
    {
        result = true;
        std::cout<<"Socket test passed."<<std::endl;
    }
    else
    {
        std::cout<<"Socket test failed."<<std::endl;
    }
    
    for(int index = 0; index < 10; index++)
    {
        list[index].Disconnect();
    }

    //clear vectors
    ports.clear();

    return true;
}

bool AcceptSocketConnections()
{
    bool result = false;
    std::vector<Server*> servers;
    std::vector<Server*>::iterator it;
    std::vector<int> ports;
    std::string ip = "127.0.0.1";
    uint16_t port = 55600;

    std::cout<<"Creating Servers..."<<std::endl;
    servers.reserve(10);

    for(int i = 0; i < 10; i++)
    {
        Server *temp = new Server(ip, port);
        servers.push_back(temp);
        port = temp->CreateListeningSocket();
        ports.push_back(port);
    }

    std::cout<<"Connecting to servers";

    std::thread clientsThread(&ClientConnectToServer, ports);

    for(std::vector<Server*>::iterator index = servers.begin(); index < servers.end(); index++)
    {
        (*index)->Accept();
    }

    std::cout<<"Verify connections were established."<<std::endl;
    std::cout<<"Launch terminal and run"<<std::endl;
    std::cout<<"Mac: lsof -i"<<std::endl<<"Raspbian: netstat -natp"<<std::endl;
    std::cout<<"Linux: netstat -A inet -p"<<std::endl;
    std::cout<<"Makes sure the following ports are use:"<<std::endl;

    for(std::vector<int>::iterator index = ports.begin(); index < ports.end(); index++)
    {
        std::cout<<(*index)<<std::endl;
    }

    std::cout<<"Are these ports in use? Y/N: ";

    char input = getchar();
    input = getchar();

    if(input == 'Y' || input == 'y')
    {
        result = true;
        std::cout<<"Socket test passed."<<std::endl;
    }
    else
    {
        std::cout<<"Socket test failed."<<std::endl;
    }
    
    for(std::vector<Server*>::iterator index = servers.begin(); index < servers.end() -1; index++)
    {
        (*index)->CloseConnection();
        (*index)->Disconnect();
        free(*index);
        it = index;
    }

    std::cout<<"Beginning to send messages over network"<<std::endl;
    std::cout<<"Server send; Client receive;"<<std::endl;

    it++;
    (*it)->Send(messages[0]);
    
    if((*it)->Read() == messages[1])
    {
        result = true;
        std::cout<<"Communicating test success"<<std::endl;
    }

    clientsThread.join();

    (*it)->CloseConnection();
    (*it)->Disconnect();
    free(*it);
}

void ClientConnectToServer(std::vector<int> ports)
{   
    std::vector<Client*> clients;
    std::vector<Client*>::iterator it;

    std::string ip = "127.0.0.1";

    clients.reserve(10);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    for(std::vector<int>::iterator i = ports.begin(); i < ports.end(); i++)
    {   
        Client *temp = new Client();
        clients.push_back(temp);
        temp->Connect(ip, (*i));
    }

    for(std::vector<Client*>::iterator index = clients.begin(); index < clients.end() -1; index++)
    {
        (*index)->Disconnect();
        free(*index);
        it = index;
    }
    it++;
    if((*it)->Read() == messages[0])
    {
        std::cout<<"Client recevied message"<<std::endl;
    }
    (*it)->Send(messages[1]);

    (*it)->Disconnect();
    free(*it);

    std::this_thread::sleep_for(std::chrono::microseconds(10));
}