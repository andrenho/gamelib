#include "game.hh"

class MyUI : public UI {

};

int main()
{
    Game game;
    game.init_ui<MyUI>();
}