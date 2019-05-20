#ifndef NETWORK_H
#define NETWORK_H
#include "Publisher.h"
#include "Customer.h"
#include "Film.h"
#include "Exception.h"


class Network{
public:
    void run();
    void handle_post_comands (std::vector <std::string> word, Person*& current_user);
    void handle_put_comands (std::vector <std::string> word, Person*& current_user);
    void handle_get_comands (std::vector <std::string> word, Person*& current_user);
    void handle_delete_comands (std::vector <std::string> word, Person*& current_user);
    void handle_signup (std::vector <std::string> word, Person*& current_user);
    void handle_login (std::vector <std::string> word, Person*& current_user);
    void add_film (std::vector <std::string> word, Person*& current_user);
    void follow(std::vector <std::string> word, Person*& current_user);
    void add_my_money (std::vector <std::string> word, Person*& current_user);
    void buy_film (std::vector <std::string> word, Person*& current_user);
    void give_my_money(Person* current_user);
    void manage_money(Film* current_film);
    void rate_film (std::vector <std::string> word, Person*& current_user);
    void comment_film (std::vector <std::string> word, Person*& current_user);
    void reply_comment (std::vector <std::string> word, Person*& current_user);
    void delete_film(std::vector <std::string> word, Person*& current_user);
    void delete_comment(std::vector <std::string> word, Person*& current_user);
private:

    std::vector<Person*> users;
    
    std::vector<Film> films;
    
    std::map<Person* , float> money_acount;

    float network_money = 0;


};









#endif