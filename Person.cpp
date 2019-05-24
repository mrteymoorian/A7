#include "Person.h"
#define EMPTY -1
#define _EMPTY ""
using namespace std;

void Person::give_notification(std::string content){ 
    notification.push_back ( Notification(content));
}

bool Person::buy_film(Film* newfilm , int price){
    if (money < price)
        throw PermissionDenid();
    if (have_bought_this_film(newfilm->get_id()))
        return false;
    money -= price;
    bought_film.push_back(newfilm);
    return true;
}

void Person::rate_film(Film* newfilm , int score){
    rated_film.push_back(newfilm);
    rated_film_with_score[newfilm] = score;
}

bool Person::has_rated_this_film(int film_id){
    for (int i = 0;i < rated_film.size() ; i++){
        if (rated_film[i]->get_id() == film_id)
            return true;
    }
    return false;
}

void Person::comment_on_this_film(int film_id, std::string content){
    for (int i = 0 ; i < bought_film.size() ; i++){
        if (bought_film[i]->get_id() == film_id){
            bought_film[i]->give_comment(content , this);
            cout << "OK" << endl;
            return;
        }
    }
    throw NotFound();
}

bool Person::have_bought_this_film(int film_id){
    for (int i = 0 ; i < bought_film.size() ; i++)
        if (bought_film[i]->get_id() == film_id)
            return true;
    return false;
}

void Person::show_purchased_films(vector <string> word){
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
    for (int i = 0 ;i < bought_film.size() ; i++){
        if (bought_film[i]->pass_the_filters(name, director, min_year, max_year, min_rate, price)){
            cout << number <<  ". " ;
            bought_film[i]->print_yourdef();
            number ++;
        }
    }

}

void Person::show_unread_notifications(){
    cout << "#. Notification Message" << endl;
    int number = 1;
    for (int i = notification.size() - 1 ; i >= 0 ; i--){
        if (!notification[i].has_been_read()){
            cout << number << ". " << notification[i].get_content()  << endl;
            notification[i].the_person_read();
            number ++;
        }
    }
}

void Person::show_read_notifications(int limit){
    cout << "#. Notification Message" << endl;
    int number = 1;
    for (int i = notification.size() - 1 ; i >= 0 ; i--){
        if (number > limit)
            return ;
        if (notification[i].has_been_read()){
            cout << number << ". " << notification[i].get_content() << endl;
            notification[i].the_person_read();
            number ++;
        }
    }
 }