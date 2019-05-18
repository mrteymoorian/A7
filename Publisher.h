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
    void reply_comment(int film_id ,int comment_id,std::string content);
private:
    
    std::vector <Film*> film;
    std::vector <Person*> followers;
    

};










#endif