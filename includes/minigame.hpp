#ifndef minigame_HPP_
#define minigame_HPP_

class Minigame
{
public:
    Minigame();
    ~Minigame();
    int run();
    void countdown(int duration, int x, int y);
    bool direction();
};

#endif 