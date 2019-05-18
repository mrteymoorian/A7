#include "Publisher.h"


using namespace std;

void Publisher::add_film(Film* NewFilm){
    film.push_back(NewFilm);
}

void Publisher::follow(Person* p){
    followers.push_back(p);
}

void Publisher::reply_comment(int film_id ,int comment_id,std::string content){
    for (int i = 0; i < film.size(); i++){
        if (film[i]->get_id() == film_id){
            film[i]->reply_comment(comment_id , content);
            return;
        }
    }
    throw NotFound();
}