#include "Film.h"
#define EMPTY -1
#define _EMPTY ""
#include <iomanip>
 
using namespace std;


void Film::set_score(int _score){
    score.push_back(_score);
    float total;
    for (int i =0 ; i< score.size() ;i++)
        total += score[i];
    int size = score.size();
    final_score = total / size;
    
    
}

void Film::set_score_again(int newscore , int oldscore){
    float total;
    for (int i =0 ; i< score.size() ;i++)
        if ( score[i] == oldscore)
            score[i] = newscore;

    for (int i =0 ; i< score.size() ;i++)
        total += score[i];
    int size = score.size();
    final_score = total / size;
    
    
}

void Film::give_comment(std::string content , Person* author){
    int _id;
    if (comment.size() != 0)
        _id = comment[comment.size() - 1].get_id() + 1;
    else 
        _id = 1;
    comment.push_back(Comment(content, _id, author));
}

void Film::reply_comment(int comment_id ,std::string content){
    for (int i = 0 ; i < comment.size() ; i++ ){
        if (comment[i].get_id() == comment_id){
            comment[i].reply(content);
            comment[i].give_author()->give_notification("Publisher " + my_publisher->get_username()
                 + " with id " + to_string(my_publisher->get_id()) + " reply to your comment.");
        }
    }
}

void Comment::reply(std::string _content){
    content.push_back(_content);
}

void Film::edit (std::string _name, int _year, int _length, int _price,std::string _summary,
        std::string _director )
{
    if (_name != _EMPTY)
        name = _name;
    if (_year != EMPTY)
        year = _year; 
    if (_length != EMPTY)
        length = _length;
    if (_price != EMPTY)
        price = _price;
    if (_summary != _EMPTY)
        summary = _summary;
    if (_director != _EMPTY)
        director = _director;

}

void Film::delete_comment(int comment_id){
    for (int i = 0;i < comment.size() ; i++){
        if (comment[i].get_id() == comment_id){
            comment.erase(comment.begin() + i);
            return ;
        }
    }
    throw NotFound();
}

void Film::print_yourdef(){
    cout << id << " | " << name << " | " << length << " | " << price << " | " <<
          final_score << " | " << year << " | " << director << endl;
}

bool Film::pass_the_filters(string _name, string _director, int min_year, int max_year, int min_rate, int  _price){
    if (_name != _EMPTY)
        if (name != _name)
            return false;
    if (_director != _EMPTY)
        if (director != _director)
            return false;
    if (_price != EMPTY)
        if (price != _price)
            return false;
    if (min_rate != EMPTY)
        if (final_score < min_rate)
            return false;

    if (min_year != EMPTY)
        if (year < min_year)
            return false;

    if (max_year != EMPTY)
        if (year > max_year)
            return false;

    return true; 
}

void Comment::print(){
    for (int i = 0 ; i < content.size() ; i++){
        if (i == 0)
            cout << id << ". " << content[i];
        else 
            cout << id << "." << i << ". " << content[i];
    }
}
void Film::show_detail(){
    cout << "Details of Film " << name << endl;
    cout << "Id = " << id << endl;
    cout << "Director = " << director << endl;
    cout << "Length = " << length << endl;
    cout << "Year = " << year << endl;
    cout << "Summary = " << summary << endl;
    cout << "Rate = " << setprecision(2) <<final_score << endl;
    cout << "Price = " << price << endl;
    cout << endl;
    cout << "Comments" << endl;
    for (int i = 0 ; i < comment.size() ; i++){
        comment[i].print();
    }
    cout << endl;
}