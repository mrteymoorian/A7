#include "Person.h"

using namespace std;

void Person::give_notification(std::string content){
    
    notification.push_back ( Notification(content));

}

void Person::buy_film(Film* newfilm , int price){
    if (money < price)
        throw PermissionDenid();
    money -= price;
    bought_film.push_back(newfilm);
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