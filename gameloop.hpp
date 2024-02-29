#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_

class Gameloop
{
    int game_mode;
public:
    Gameloop(int theGame_mode);
    ~Gameloop();
    int run();
};

#endif 