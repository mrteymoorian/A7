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



private:
    
    std::vector <Film*> bought_film;
   

};









#endif