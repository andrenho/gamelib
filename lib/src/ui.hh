#ifndef UI_HH
#define UI_HH

#include <SDL3/SDL.h>

#include <string>

#include "scene.hh"


namespace gb {

class UI {
public:
    UI(std::string const& title, int w, int h, SDL_WindowFlags flags=0);
    virtual ~UI();

    virtual SDL_AppResult       event(SDL_Event* event) = 0;
    [[nodiscard]] virtual Scene create_scene() const = 0;
    virtual void                render() const {}

    void render_scene(Scene const& scene) const;
    void render_present() const;

    [[nodiscard]] SDL_Window*   window() const { return window_; }
    [[nodiscard]] SDL_Renderer* ren() const { return ren_; }

protected:
    SDL_Window* window_;
    SDL_Renderer* ren_;
};

}

gb::UI const& U();

#endif //UI_HH
