#ifndef FILM_H
#define FILM_H
#include <iostream>
#include <string>
#include <vector>

class Film{
public:
    Film (std::string _name, int _year, int _length, int _price,std::string _summary,
        std::string _director , int _id)
    {
        name = _name;
        year = _year;
        length = _length;
        price = _price;
        summary = _summary;
        director = _director;
        id = _id;
    }


private:
    std::string name;
    int year;
    int length;
    int price;
    std::string summary;
    std::string director;
    int id;
    float score = 0;
    std::vector <std::string> comments;


};










#endif