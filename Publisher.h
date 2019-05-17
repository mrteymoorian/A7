#ifndef PUBLISHER_H
#define PUBLISHER_H
#include <iostream>
#include <string>
#include <vector>

#include "Person.h"


class Publisher : public Person{
public:
    Publisher(std::string user, std::string pass , std::string _email, int _age, int _id)
    : Person(user, pass, _email, _age, _id){}
    std::string get_type(){ return "publisher";}

    void add_film(Film* NewFilm);
    void follow(Person* p);
private:
    
    std::vector <Film*> film;
    std::vector <Person*> followers;
    

};










#endif