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
    void handle_put_comands ();
    void handle_get_comands ();
    void handle_delet_comands ();
    void handle_signup (std::vector <std::string> word, Person*& current_user);
    void handle_login (std::vector <std::string> word, Person*& current_user);
    void add_film (std::vector <std::string> word, Person*& current_user);
    void follow(std::vector <std::string> word, Person*& current_user);
private:

    std::vector<Person*> users;
    
    std::vector<Film> films;
    
    int money = 0;


};









#endif