#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <string>
#include <vector>
#include "Person.h"


class Customer : public Person{
public:
    Customer(std::string user, std::string pass , std::string _email, int _age, int _id)
    : Person(user, pass, _email, _age, _id){}
    std::string get_type(){ return "customer";}
    void follow(Person* p);
    

private:
    
    
    std::vector <Person*> following;

};









#endif