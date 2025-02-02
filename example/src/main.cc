#include "gamelib.hh"

class MyGame : public gb::Game {
public:
    using Game::Game;

    void update() override {}

    [[nodiscard]] std::string name() const override { return "example"; }
    [[nodiscard]] std::string version() const override { return "0.0.1"; }
    [[nodiscard]] std::string app_identifier() const override { return "example.com"; }
};

class MyUI : public gb::UI {
public:
    using UI::UI;

    [[nodiscard]] gb::Scene create_scene() const override
    {
        return {};
    }

    SDL_AppResult event(SDL_Event* event) override
    {
        if (event->type == SDL_EVENT_QUIT)
            return SDL_APP_SUCCESS;
        return SDL_APP_CONTINUE;
    }
};

gb::Game const& G(int argc, char* argv[])
{
    static MyGame game(argc, argv);
    return game;
}

gb::UI const& UI()
{
    static MyUI ui("Example", 800, 600);
    return ui;
}