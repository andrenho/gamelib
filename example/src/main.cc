#include "game.hh"

class MyGame : public Game {
public:
    [[nodiscard]] std::string name() const override { return "example"; }
    [[nodiscard]] std::string version() const override { return "0.0.1"; }
    [[nodiscard]] std::string app_identifier() const override { return "example.com"; }
};

Game* Game::instance(int argc, char* argv[])
{
    static MyGame game;
    return &game;
}
