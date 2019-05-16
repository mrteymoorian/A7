#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
#include <vector>
#include "Film.h"
#include "Exception.h"

class Person{
public:
    Person(std::string user, std::string pass , std::string _email, int _age , int _id){
        username = user:
        password = pass;
        email = _email;
        age = _age;
        id = _id;
        
    }





protected:
    std::string username;
    std::string password;
    std::string email;
    int age;
    int id;
    int money;
    std::vector< std::string> notification;
    

};










#endif