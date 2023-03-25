#include "score.h"

Score::Score(int score)
    : current_score_(score) 
    {check_highscore();}

int Score::gethighscore()
{
    std::ifstream indata;
    indata.open("../high_score.txt");
    
    std::string s;
    if(indata.is_open())
    {
        getline(indata, s);
        highscore_= std::stoi(s);
        return highscore_;
    }
    else
    {
        return 0;
    }
}

int Score::write_tofile()
{
    std::ofstream outdata;

    outdata.open("../high_score.txt");
    if(!outdata)
    {
        std::cerr << "Cant write to Score to file" << std::endl;
        return -1;
    }

    outdata << highscore_ << std::endl;
    outdata.close();
    return 0;
}

void Score::check_highscore()
{
    std::ifstream indata;
    indata.open("../high_score.txt");
    
    std::string s;
    if(indata.is_open())
    {
        getline(indata, s);
        highscore_= std::stoi(s);
        if(current_score_ >std::stoi(s))
        {
        std::cout<<"You got Highscore !"<<std::endl;
        highscore_=current_score_;
        write_tofile();
        }
        else
        std::cout<<"Better Luck next time..Keep pushing!"<<std::endl;
    }
    else
    {
        highscore_=current_score_;
        write_tofile();
    }

}