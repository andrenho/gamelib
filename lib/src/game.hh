#ifndef GAME_HH
#define GAME_HH

#include <memory>
#include <string>

class Game {
public:
    virtual ~Game() = default;

    [[nodiscard]] virtual std::string name() const = 0;
    [[nodiscard]] virtual std::string version() const = 0;
    [[nodiscard]] virtual std::string app_identifier() const = 0;

    static Game* instance(int argc, char* argv[]);

protected:
    Game() = default;
};

#endif //GAME_HH
