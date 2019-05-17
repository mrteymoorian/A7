#ifndef FILM_H
#define FILM_H
#include <iostream>
#include <string>
#include <vector>
#include "Person.h"

class Person;

class Film{
public:
    Film (std::string _name, int _year, int _length, int _price,std::string _summary,
        std::string _director , int _id , Person* _my_publisher)
    {
        name = _name;
        year = _year;
        length = _length;
        price = _price;
        summary = _summary;
        director = _director;
        id = _id;
        my_publisher = _my_publisher;
    }
    std::string get_name(){ return name;}
    int get_id(){ return id;}
    int get_price(){ return price;}
    void set_score(int _score);
    void set_score_again(int newscore , int oldscore);
    Person* publisher(){ return my_publisher;}
    

private:
    std::string name;
    int year;
    int length;
    int price;
    std::string summary;
    std::string director;
    int id;
    float final_score = 0;
    std::vector <int > score;
    std::vector <std::string> comments;
    Person* my_publisher;
    //std::vector <Person*> person_bought_me;


};










#endif