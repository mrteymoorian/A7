#ifndef FILM_H
#define FILM_H
#include <iostream>
#include <string>
#include <vector>
#include "Person.h"

class Person;

class Comment{
public:
    Comment(std::string _content, int _id , Person* _author){
        content.push_back(_content);
        id = _id;
        author = _author;
    }
    int get_id() { return id;}
    void reply(std::string _content);
    Person* give_author(){ return author;}
    void print();
private:
    std::vector<std::string> content;
    int id;
    Person* author;

};


class Film{
public:
    Film (std::string _name, int _year, int _length, int _price,std::string _summary,
        std::string _director , int _id , Person* _my_publisher)
    {
        name = _name;
        year = _year;
        length = _length;
        price = _price;
        summary = _summary;
        director = _director;
        id = _id;
        my_publisher = _my_publisher;
    }
    bool deleted() { return has_been_deldeted;}
    void delete_yourself(){ has_been_deldeted = true;}
    void delete_comment(int comment_id);
    std::string get_director(){ return director;}
    std::string get_name(){ return name;}
    int get_id(){ return id;}
    int get_price(){ return price;}
    int get_length(){ return length;}
    float get_final_score(){ return final_score;}
    void set_score(int _score);
    void set_score_again(int newscore , int oldscore);
    Person* publisher(){ return my_publisher;}
    void give_comment(std::string content , Person* author);
    void reply_comment(int comment_id ,std::string content);
    void edit (std::string _name, int _year, int _length, int _price,std::string _summary,
        std::string _director );
    void print_yourdef();
    bool pass_the_filters(std::string _name,std::string _director, int min_year, int max_year, int min_rate, int  _price);
    void show_detail();

private:
    std::string name;
    int year;
    int length;
    int price;
    std::string summary;
    std::string director;
    int id;
    float final_score = 0;
    bool has_been_deldeted = false;
    std::vector <int > score;
    std::vector <Comment> comment;
    Person* my_publisher;
    //std::vector <Person*> person_bought_me;


};










#endif