#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
#include <vector>
#include "Film.h"
#include "Exception.h"

class Notification{
public:
    Notification(std::string _content){ content = _content;}

private:
    std::string content;
    bool read = false;

};



class Person{
public:
    Person(std::string user, std::string pass , std::string _email, int _age , int _id){
        username = user;
        password = pass;
        email = _email;
        age = _age;
        id = _id;
        
    }
    std::string get_username(){ return username;}
    std::string get_password(){ return password;}
    int get_id(){ return id;}
    virtual std::string get_type () = 0;
    virtual void add_film(Film* NewFilm){}
    virtual void follow(Person* p){}
    void give_notification(std::string content);
    



protected:
    std::string username;
    std::string password;
    std::string email;
    int age;
    int id;
    int money;
    std::vector <Notification> notification;
    

};










#endif