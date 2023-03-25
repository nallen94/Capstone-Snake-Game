#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <fstream>

class Score
{
    public:
        Score() {};
        Score(const int);
        int gethighscore();
        int write_tofile();
        void check_highscore();

    private:
        int current_score_; 
        int highscore_;
};

#endif