#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <string>
#include <vector>

class Customer : public Person{
    Customer(std::string user, std::string pass , std::string _email, int _age, int _id)
    : Person(usre, pass, _email, _age, _id)



private:
    
    std::vector <Film*> bought_film;
   

};









#endif