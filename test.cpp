#include "Client.hpp"

int main()
{
  string input;
  getline(cin, input);
  cout<<input<<endl;

  Client hi;
  int id = hi.Connect("127.0.0.1", 55500);

  cout<<id<<endl;

  string ehllo;
  getline(cin, ehllo);
  cout<<ehllo<<endl;
}