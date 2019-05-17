#include "Film.h"

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

