#include <iostream>
#include <thread>
#include <chrono>
#include <termios.h>

using namespace std;

static struct termios old, newt;

void clear()
{
  for(int i = 0; i < 100; i++)
  {
    cout<<endl;
  }
}

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  newt = old; /* make new settings same as old settings */
  
  if (echo) {
    newt.c_lflag |= ECHO | ECHOE | TCIOFLUSH; /* set echo mode */
  } else {
    newt.c_lflag &= ~ECHO; /* set no echo mode */
  }
  //tcsetattr(0, TCSANOW, &old);
  tcsetattr(0, TCSANOW, &newt); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  //initTermios(echo);
  ch = getchar();
  //resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}

int main()
{
    string buffer;
    buffer.clear();

    while(true)
    {
        initTermios(1);

        char input = getche();

        if(input == 'q')
        {
            cout<<"entered delete";
            std::this_thread::sleep_for(chrono::seconds(2));
            //tcflush(0, TCIOFLUSH); //does not let q print to screen. 
        }
        if(input != '\n')
        {
            buffer+=input;
        }
        else
        {
           clear();
            cout<<buffer;
            buffer.clear();
        }
        
        
        
    }
}    