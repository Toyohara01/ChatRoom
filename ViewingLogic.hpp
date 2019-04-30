#ifndef VIEWINGLOGIC_HPP
#define VIEWINGLOGIC_HPP

#include<iostream> 
#include<vector>
#include<iterator> 

class ViewingLogic
{
private:

public:
    enum AppendModes {SEND, RECEIVE};

    //Has implicit constructor. 
    void CreateWindow();
    void AppendWindow(AppendModes appendMode);
    void ClearLine();
    void ClearWindow();

    static void Display(std::vector<std::string> input);
};

#endif //VIEWINGLOGIC_HPP