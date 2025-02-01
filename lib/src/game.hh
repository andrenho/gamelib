#ifndef GAME_HH
#define GAME_HH

#include <memory>

#include "ui.hh"

class Game {
public:
    template <typename T, typename... Args>
    void init_ui(Args&&... args) {
        ui_ = std::make_unique<T>(args...);
    }

    [[nodiscard]] UI& ui() const { return *ui_; }

private:
    std::unique_ptr<UI> ui_;
};

#endif //GAME_HH
