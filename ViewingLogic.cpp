#include "ViewingLogic.hpp"

void ViewingLogic::CreateWindow()
{

}

void ViewingLogic::AppendWindow(ViewingLogic::AppendModes appendMode)
{

}

void ViewingLogic::ClearLine()
{

}

void ViewingLogic::ClearWindow()
{
    
}

static void Display(std::vector<std::string> input)
{
    const char otherUserDelim = ':';

    for(std::vector<std::string>::iterator it = input.begin(); it < input.end(); it++)
    {
        std::string temp = (*it);

        if(temp.find(otherUserDelim) < 0)
        {
            std::cout<<"\t\t" + temp<<std::endl;
        }
        else
        {
            std::cout<<temp<<std::endl;
        }
        
    }
}