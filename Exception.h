#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <vector>
#include <iostream>
#include <exception>

class NotFound : public std::exception
{
public:
    virtual const char* what() const throw()
  {
    return "Not Found";
  }

};

class BadRequest : public std::exception
{
public:
    virtual const char* what() const throw()
  {
    return "Bad Request";
  }

};

class PermissionDenid : public std::exception
{
public:
    virtual const char* what() const throw()
  {
    return "Permission Denied";
  }

};






#endif