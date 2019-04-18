#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>

using namespace std;

class ReadError: public exception
{
  virtual const char* what() const throw()
  {
    return "Error Reading from socket ";
  }
};

#endif //EXCEPTION_HPP