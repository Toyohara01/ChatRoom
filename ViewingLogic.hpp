#ifndef VIEWINGLOGIC_HPP
#define VIEWINGLOGIC_HPP

#include <curses.h>

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


};

#endif //VIEWINGLOGIC_HPP