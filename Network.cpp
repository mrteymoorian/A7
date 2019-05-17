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
    
    
    films.push_back(Film(name, stoi(year), stoi(length), stoi(price) , summary , director, films.size() + 1));
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
        if (current_user->get_type() == "customer"){
            follow(word, current_user);
        }
        else 
            throw PermissionDenid();    
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
            cout << e.what() <<endl;
        }
        
        if (word[0] == POST){
            try{
                handle_post_comands(word , current_user);
            }catch(exception& e){
                cout << e.what() <<endl;
            }
        }



    }

}