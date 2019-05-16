#ifndef PUBLISHER_H
#define PUBLISHER_H
#include <iostream>
#include <string>
#include <vector>
#include "Film.h"
#include "Person.h"


class Publisher : public Person{
    Publisher(std::string user, std::string pass , std::string _email, int _age, int _id)
    : Person(usre, pass, _email, _age, _id)



private:
    
    std::vector <Film*> film;
    std::vector <Person*> followers;
    

};










#endif