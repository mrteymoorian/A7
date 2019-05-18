#include "Film.h"
#define EMPTY -1
#define _EMPTY ""
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
    if (comment.size() != 0)
        id = comment[comment.size() - 1].get_id() + 1;
    else 
        id = 1;
    comment.push_back(Comment(content, id, author));
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