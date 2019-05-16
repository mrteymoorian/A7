#ifndef FILM_H
#define FILM_H
#include <iostream>
#include <string>
#include <vector>

class Film{

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