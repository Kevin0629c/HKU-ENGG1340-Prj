#ifndef minigame_HPP_
#define minigame_HPP_

class Minigame
{
public:
    Minigame();
    ~Minigame();
    int run();
    void countdown(int x, int y);
    void bar(int &pos);
    bool direction();
};

#endif 