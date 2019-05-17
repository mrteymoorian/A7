#include "Network.h"
#include <sstream>
#define  POST "POST"
#define  PUT "PUT"
#define  GET "GET"
#define  DELET "DELET"
using namespace std;


void Network::handle_post_comands (vector <string> word, Person*& current_user){
     if (word[1] != "signup" && word[1] != "login" && word[1] != "films" &&
         word[1] != "money" && word[1] != "replies" && word[1] != "followers" &&
         word[1] != "buy" && word[1] != "rate" && word[1] != "comments")
                throw NotFound();
                
    if (word[1] == "signup"){
        if (word.size() == 11){
            users.push_back( new Customer(word[6], word[8], word[4], stoi(word[10]), users.size()+1));
        }
        if (word.size() == 13){
            users.push_back( new Publisher(word[6], word[8], word[4], stoi(word[10]), users.size()+1));
        }
        if (word.size() != 11 && word.size() != 13)
            throw BadRequest();
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