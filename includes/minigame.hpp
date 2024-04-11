#ifndef minigame_HPP_
#define minigame_HPP_

class Minigame
{
public:
    Minigame();
    ~Minigame();
    bool run();
    bool countdown(int winCols, int winRows);
    bool stopCountdown=false;
    bool direction();
};

#endif 