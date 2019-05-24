#include "Publisher.h"
#include <string>
#define EMPTY -1
#define _EMPTY ""

using namespace std;

void Publisher::add_film(Film* NewFilm){
    film.push_back(NewFilm);
}

bool Publisher::follow(Person* p){
    for (int i = 0 ; i < followers.size() ; i++)
        if (followers[i] == p)
            return false;
    followers.push_back(p);
    return true;
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

void Publisher::delete_film(int film_id){
    for (int i = 0;i < film.size() ; i++){
        if (film[i]->get_id() == film_id){
            film[i]->delete_yourself();
            cout << "OK" << endl;
            return ;
        }
    }
    throw PermissionDenid();
}

void Publisher::show_followers(){
    cout << "List of Followers" << endl;
    cout << "#. User Id | User Username | User Email" << endl;
    for (int i = 0 ;i < followers.size() ; i++){
        cout << i+1 << ". " << followers[i]->get_id() << " | " <<
            followers[i]->get_username() << " | " << followers[i]->get_email() <<endl;
    }

}

void Publisher::show_published_films(std::vector <std::string> word){
    string name = _EMPTY , director = _EMPTY;
    int min_year = EMPTY, max_year = EMPTY , price = EMPTY , min_rate = EMPTY;
    for (int i = 3; i < word.size() - 1 ; i++ ){
        if (word[i] == "name")
            name = word[i+1];
        if (word[i] == "director")
            director = word[i+1];
        if (word[i] == "max_year")
            max_year = stoi(word[i+1]);
        if (word[i] == "min_year")
            min_year = stoi(word[i+1]);
        if (word[i] == "price")
            price = stoi(word[i+1]);
        if (word[i] == "min_rate")
            min_rate = stoi(word[i+1]);
    }
    int number = 1;
    cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << endl;
    for (int i = 0 ;i < film.size() ; i++){
        if (film[i]->pass_the_filters(name, director, min_year, max_year, min_rate, price) && !film[i]->deleted()){
            cout << number <<  ". " ;
            film[i]->print_yourdef();
            number ++;
        }
    }
}