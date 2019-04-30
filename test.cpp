#include "Client.hpp"

#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

class test
{
private: 
  
public:
  int x;
  test(int x)
  {
    this->x = x;
  }
};

int main()
{
  vector<test> hello;
  hello.reserve(8);

  cout<<hello.size()<<endl;
  for(int index = 0; index < 8; index++)
  {
    hello.push_back(test(index));
  }

  cout<<hello.size();
  vector<test>::iterator it = hello.end() - 1;
  cout<<(*it).x;



  // hi;
  // /int id = hi.Connect("127.0.0.1", 55500);

  //cout<<id<<endl;

  string ehllo;
  getline(cin, ehllo);
  cout<<ehllo<<endl;
}