#ifndef UI_HH
#define UI_HH

#include <SDL3/SDL.h>

#include <string>

#include "scene.hh"


namespace gb {

class UI {
public:
    UI(std::string const& title, int w, int h, SDL_WindowFlags flags=0);
    ~UI();

    virtual SDL_AppResult event(SDL_Event* event) = 0;
    virtual Scene create_scene() const = 0;
    virtual void render() const {}

    void render_scene(Scene const& scene) const;
    void render_present() const;

protected:
    SDL_Window* window;
    SDL_Renderer* ren;
};

}

gb::UI const& UI();

#endif //UI_HH
