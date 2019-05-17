#include "Network.h"
#include <sstream>
#include <string>
#define  POST "POST"
#define  PUT "PUT"
#define  GET "GET"
#define  DELET "DELET"
#define OK "OK"
using namespace std;

void Network::handle_signup (vector <string> word, Person*& current_user){
    
    if (word.size() != 11 && word.size() != 13)
        throw BadRequest();
    
    string username, password, email, age, publisher;
    for (int i = 3; i < word.size() ; i = i + 2){
        if (word[i] == "username")
            username = word[i+1];
        if (word[i] == "password")
            password = word[i+1];
        if (word[i] == "email")
            email = word[i+1];
        if (word[i] == "age")
            age = word[i+1];
        if (word[i] == "publisher")
            publisher = word[i+1];
    }

    for (int i = 0 ; i < users.size() ; i++)
        if (username == users[i]->get_username() )
            throw BadRequest();
            
    if (word.size() == 11){
            users.push_back( new Customer(username, password, email, stoi(age), users.size()+1));
            cout << OK << endl;
            current_user = users[users.size() - 1];       
    }
    if (word.size() == 13 && publisher == "true"){
            users.push_back( new Publisher(username, password, email, stoi(age), users.size()+1));
            cout << OK << endl;
            current_user = users[users.size() - 1];
    }
    if (word.size() == 13 && publisher == "false"){
            users.push_back( new Customer(username, password, email, stoi(age), users.size()+1));
            cout << OK << endl;
            current_user = users[users.size() - 1];
    }

}

void Network::handle_login (vector <string> word, Person*& current_user){
    string username, password;
    for (int i = 3; i < word.size() ; i = i + 2){
        if (word[i] == "username")
            username = word[i+1];
        if (word[i] == "password")
            password = word[i+1];
    }
    for (int i = 0 ; i < users.size() ; i++){
        if (username == users[i]->get_username() && password == users[i]->get_password())
            current_user = users[i];
            cout << OK <<endl;
            return ;
    }
    throw BadRequest();
}

void Network::add_film (vector <string> word, Person*& current_user){
    if (word.size() != 15)
        throw BadRequest();
    string name, year, length, price , summary , director;
    for (int i = 3; i < word.size() ; i = i + 2){
        if (word[i] == "name")
            name = word[i+1];
        if (word[i] == "year")
            year = word[i+1];
        if (word[i] == "length")
            length = word[i+1];
        if (word[i] == "price")
            price = word[i+1];
        if (word[i] == "summary")
            summary = word[i+1];
        if (word[i] == "director")
            director = word[i+1];
    }
    
    
    films.push_back(Film(name, stoi(year), stoi(length), stoi(price) , summary , director, films.size() + 1, current_user));
    current_user->add_film(& films[films.size() - 1]);
    cout << OK <<endl;
}

void Network::follow (vector <string> word, Person*& current_user){
    if (word.size() != 5)
        throw BadRequest();
    string user_id = word[4];
    for (int i = 0 ; i < users.size() ; i++){
        if (stoi(user_id) == users[i]->get_id() && users[i]->get_type() == "publisher"){
            users[i]->follow(current_user);
            users[i]->give_notification("User " + current_user->get_username() +
                " with id " + to_string(current_user->get_id()) + " follow you.");
            current_user->follow(users[i]);
            cout << OK <<endl;
            return;
        }
    }
    throw NotFound();


}


void Network::add_my_money (vector <string> word, Person*& current_user){
    if (word.size() != 5)
        throw BadRequest();

    int amount = stoi(word[4]);
    current_user->inc_money(amount); 
    cout << OK <<endl;
}

void Network::buy_film (vector <string> word, Person*& current_user){
    if (word.size() != 5)
        throw BadRequest();
    int film_id = stoi(word[4]);
    for (int i = 0 ;i < films.size() ; i++){
        if (film_id == films[i].get_id()){
            current_user->buy_film(&films[i] , films[i].get_price());
            network_money += films[i].get_price();
            films[i].publisher()->give_notification("User " + current_user->get_username() +
                " with id " + to_string(current_user->get_id()) + " buy your film " + films[i].get_name() +
               " with id " + to_string(films[i].get_id()) );
            cout << OK <<endl;
            return;
        }
    }
    throw NotFound();


}

void Network::rate_film (vector <string> word, Person*& current_user){
    if (word.size() != 7)
        throw BadRequest();
    int film_id, score;
    for (int i = 3; i < word.size() ; i = i + 2){
        if (word[i] == "film_id")
            film_id = stoi(word[i+1]);
        if (word[i] == "score")
            score = stoi(word[i+1]);
    }
    
    for (int i = 0 ;i < films.size() ; i++){
        if (film_id == films[i].get_id()){ 
            if (!current_user->has_rated_this_film(film_id))   
                films[i].set_score(score);
            else
                films[i].set_score_again(score , current_user->get_score_of_this_film(&films[i]) );
            current_user->rate_film(&films[i] , score);
            films[i].publisher()->give_notification("User " + current_user->get_username() +
                " with id " + to_string(current_user->get_id()) + " rate your film " + films[i].get_name() +
                " with id " + to_string(films[i].get_id()) );
            cout << OK <<endl;
            return;
        }
    }
    throw NotFound();
}

void Network::handle_post_comands (vector <string> word, Person*& current_user){
     if (word[1] != "signup" && word[1] != "login" && word[1] != "films" &&
         word[1] != "money" && word[1] != "replies" && word[1] != "followers" &&
         word[1] != "buy" && word[1] != "rate" && word[1] != "comments")
                throw NotFound();

    if (word[1] == "signup"){
        handle_signup(word, current_user);    
    }
    if (word[1] == "login"){
        handle_login(word, current_user);    
    }
    if (word[1] == "films"){
        if (current_user->get_type() == "publisher"){
            add_film(word, current_user);
        }
        else 
            throw PermissionDenid();    
    }
    if (word[1] == "followers"){    
        follow(word, current_user);
    }
    if (word[1] == "money" && word.size() > 2){    
        add_my_money(word, current_user);
    }
    if (word[1] == "buy"){    
        buy_film(word, current_user);
    }
    if (word[1] == "rate"){    
        rate_film(word, current_user);
    }




}

void Network::run(){
    string input;
    Person* current_user = NULL;
    while (getline( cin, input)){
        string temp_word;
        vector <string> word;
        istringstream buf(input);
        while(buf >> temp_word)
            word.push_back(temp_word);
        
        try{
            if (word[0] != POST && word[0] != PUT && word[0] != GET && word[0] != DELET)
                throw BadRequest();
        }catch(exception& e){
            if (e.what() == "stoi")
                cout << "Bad Request" <<endl;
            else
                cout << e.what() <<endl;
        }
        
        if (word[0] == POST){
            try{
                handle_post_comands(word , current_user);
            }catch(exception& e){
                if (e.what() == "stoi")
                    cout << "Bad Request" <<endl;
                else
                    cout << e.what() <<endl;
            }
        }



    }

}