#ifndef GAME_HH
#define GAME_HH

#include <string>

namespace gb {

class Game {
public:
    Game([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {}
    virtual ~Game() = default;

    virtual void update() = 0;
    virtual void before_quit() {}

    [[nodiscard]] virtual std::string name() const = 0;
    [[nodiscard]] virtual std::string version() const = 0;
    [[nodiscard]] virtual std::string app_identifier() const = 0;
};

}

gb::Game const& G(int argc=0, char* argv[]={});

#endif //GAME_HH
