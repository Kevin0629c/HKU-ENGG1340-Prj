#ifndef minigame_HPP_
#define minigame_HPP_

class Minigame
{
    int game_mode;
public:
    Minigame(int theGame_mode);
    ~Minigame();
    int run();
};

#endif 