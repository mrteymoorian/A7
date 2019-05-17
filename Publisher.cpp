#include "Publisher.h"


using namespace std;

void Publisher::add_film(Film* NewFilm){
    film.push_back(NewFilm);
}

void Publisher::follow(Person* p){
    followers.push_back(p);
}