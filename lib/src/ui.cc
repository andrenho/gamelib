#include "ui.hh"

namespace gb {

UI::UI(std::string const& title, int w, int h, SDL_WindowFlags flags)
    : window(SDL_CreateWindow(title.c_str(), w, h, flags)),
      ren(SDL_CreateRenderer(window, nullptr))
{

}

UI::~UI()
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
}

void UI::render_scene(Scene const& scene) const
{

}

void UI::render_present() const
{
    SDL_RenderPresent(ren);
}

}
