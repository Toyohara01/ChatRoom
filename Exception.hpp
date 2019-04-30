#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>

class NetworkError: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Error Reading from socket ";
  }
};

#endif //EXCEPTION_HPP