#include "Network.h"
#include <sstream>
#include <string>
#define  POST "POST"
#define  PUT "PUT"
#define  GET "GET"
#define  DELETE "DELETE"
#define OK "OK"
#define EMPTY -1
#define _EMPTY ""
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
            money_acount[current_user] = 0;
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
void Network::manage_money(Film* current_film){
    
    if (current_film->get_final_score() < 5){
       money_acount[ current_film->publisher()] += 0.8 * current_film->get_price();
       network_money += 0.2 * current_film->get_price();
    }
    if (current_film->get_final_score() >= 5 && current_film->get_final_score() < 8){
       money_acount[ current_film->publisher()] += 0.9 * current_film->get_price();
       network_money += 0.1 * current_film->get_price();
    }
    if (current_film->get_final_score() >= 8){
       money_acount[ current_film->publisher()] += 0.95 * current_film->get_price();
       network_money += 0.05 * current_film->get_price();
    }


}
void Network::buy_film (vector <string> word, Person*& current_user){
    if (word.size() != 5)
        throw BadRequest();
    int film_id = stoi(word[4]);
    for (int i = 0 ;i < films.size() ; i++){
        if (film_id == films[i].get_id()){
            current_user->buy_film(&films[i] , films[i].get_price());
            manage_money(&films[i]);
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

void Network::comment_film (vector <string> word, Person*& current_user){
    if (word.size() != 7)
        throw BadRequest();
    int film_id;
    string content;
    for (int i = 3; i < word.size() ; i = i + 2){
        if (word[i] == "film_id")
            film_id = stoi(word[i+1]);
        if (word[i] == "content")
            content = word[i+1];
    }
    
   current_user->comment_on_this_film(film_id , content);

   for (int i = 0 ;i < films.size() ; i++){
        if (film_id == films[i].get_id()){ 
            films[i].publisher()->give_notification("User " + current_user->get_username() +
                " with id " + to_string(current_user->get_id()) + " comment on your film " + films[i].get_name() +
                " with id " + to_string(films[i].get_id()) );
            cout << OK <<endl;
            return;
        }
    }
    
}

void Network::reply_comment(vector <string> word, Person*& current_user){
    if (word.size() != 9)
        throw BadRequest();
    int film_id;
    int comment_id;
    string content;
    for (int i = 3; i < word.size() ; i = i + 2){
        if (word[i] == "film_id")
            film_id = stoi(word[i+1]);
        if (word[i] == "comment_id")
            comment_id = stoi(word[i+1]);
        if (word[i] == "content")
            content = word[i+1];
    }
    
    current_user->reply_comment(film_id , comment_id, content);
    cout << OK <<endl;
    return;
    
}

void Network::give_my_money(Person* current_user){
    current_user->inc_money(money_acount[current_user]);
    money_acount[current_user] = 0;
    cout << OK << endl;
}

void Network::handle_post_comands (vector <string> word, Person*& current_user){
     if (word[1] != "signup" && word[1] != "login" && word[1] != "films" &&
         word[1] != "money" && word[1] != "replies" && word[1] != "followers" &&
         word[1] != "buy" && word[1] != "rate" && word[1] != "comments")
                throw NotFound();

    if (word[1] == "signup"){
        handle_signup(word, current_user);    
    }
    if (current_user == NULL)
        throw PermissionDenid();
        
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

    if (word[1] == "replies"){
        if (current_user->get_type() == "publisher"){
            reply_comment(word, current_user);
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
    if (word[1] == "money" && word.size() == 2){    
        if (current_user->get_type() == "publisher")
            give_my_money(current_user);
        else
            throw PermissionDenid();  
    }
    if (word[1] == "buy"){    
        buy_film(word, current_user);
    }
    if (word[1] == "rate"){    
        rate_film(word, current_user);
    }
    if (word[1] == "comments"){    
        comment_film(word, current_user);
    }


}

void Network::handle_put_comands (vector <string> word, Person*& current_user){
    if (word[1] != "films")
        throw NotFound();
    if (current_user->get_type() != "publisher")
        throw PermissionDenid();
    int film_id, year = EMPTY, length = EMPTY, price = EMPTY;
    string name = _EMPTY , summary = _EMPTY , director = _EMPTY;
    for (int i = 3; i < word.size() - 1 ; i++ ){
        if (word[i] == "film_id")
            film_id = stoi(word[i+1]);
        if (word[i] == "name")
            name = word[i+1];
        if (word[i] == "year")
            year = stoi(word[i+1]);
        if (word[i] == "length")
            length = stoi(word[i+1]);
        if (word[i] == "price")
            price = stoi(word[i+1]);
        if (word[i] == "summary")
            summary = word[i+1];
        if (word[i] == "director")
            director = word[i+1];
    }

    for (int i = 0; i < films.size() ; i++ ){
        if (films[i].get_id() == film_id){
            if (films[i].publisher() == current_user){
                films[i].edit(name, year, length, price, summary, director);
                cout << OK << endl;
            }
            else
                throw BadRequest();
            
        }
    }

}

void Network::delete_film(vector <string> word, Person*& current_user){
    if (word.size() != 5)
        throw BadRequest();
    int film_id , flag = 0;
    if (word[3] == "film_id")
        film_id = stoi(word[4]);
    else 
        throw BadRequest();
    for (int i = 0 ; i < films.size() ; i++ )
        if( films[i].get_id() == film_id)
            flag = 1;
    if (flag == 0)
        throw NotFound();    
    
    current_user->delete_film(film_id);

}
void Network::delete_comment(vector <string> word, Person*& current_user){
    if (word.size() != 7)
        throw BadRequest();
    int film_id , comment_id;
    for (int i = 3; i < word.size() ; i = i + 2){
        if (word[i] == "film_id")
            film_id = stoi(word[i+1]);
        if (word[i] == "comment_id")
            comment_id = stoi(word[i+1]);
    }
    
    for (int i = 0; i < films.size() ; i++){
        if (films[i].get_id() == film_id && films[i].publisher() == current_user){
            films[i].delete_comment(comment_id);
        }
    }

}
void Network::handle_delete_comands (vector <string> word, Person*& current_user){
    if (word[1] != "films" && word[1] != "comments")
        throw NotFound(); 
    if (current_user->get_type() != "publisher")
        throw PermissionDenid();
    if (word[1] == "films"){
        delete_film(word, current_user);
    }
    if (word[1] == "comments"){
        delete_comment(word, current_user);
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
        if (word.size() == 0)
            continue;
        
        try{
            if (word[0] != POST && word[0] != PUT && word[0] != GET && word[0] != DELETE)
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

        if (word[0] == PUT){
            try{
                if (current_user == NULL)
                    throw PermissionDenid();
                handle_put_comands(word , current_user);
            }catch(exception& e){
                if (e.what() == "stoi")
                    cout << "Bad Request" <<endl;
                else
                    cout << e.what() <<endl;
            }
        }
        if (word[0] == DELETE){
            try{
                if (current_user == NULL)
                    throw PermissionDenid();
                handle_delete_comands(word , current_user);
            }catch(exception& e){
                if (e.what() == "stoi")
                    cout << "Bad Request" <<endl;
                else
                    cout << e.what() <<endl;
            }
        }

    }

}