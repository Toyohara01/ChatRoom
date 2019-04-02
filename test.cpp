#include <iostream>
#include <thread>
#include <termios.h>

using namespace std;

static struct termios old, newt;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  newt = old; /* make new settings same as old settings */
  //newt.c_lflag &= ICANON; /* disable buffered i/o */
  //newt.c_iflag = ISTRIP | ICRNL | INLCR | IXANY;
  //newt.c_oflag = BSDLY | ONLCR | ONOCR | CRDLY | NLDLY | ONLRET;
  //newt.c_ospeed = BS0 | CR0 | NL0;
  //newt.c_cc[0] = VERASE;
  //newt.c_cc[1] = VEOL;
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
            std::this_thread::sleep_for(2);
            tcflush(0, TCIOFLUSH); //does not let q print to screen. 
        }
        /*if(input != '\n')
        {
            buffer+=input;
        }
        else
        {
            cout<<buffer<<endl;
            buffer.clear();
        }*/
        
        
        
    }
}    