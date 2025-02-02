#include "ui.hh"

namespace gb {

UI::UI(std::string const& title, int w, int h, SDL_WindowFlags flags)
    : window_(SDL_CreateWindow(title.c_str(), w, h, flags)),
      ren_(SDL_CreateRenderer(window_, nullptr))
{

}

UI::~UI()
{
    SDL_DestroyRenderer(ren_);
    SDL_DestroyWindow(window_);
}

void UI::render_scene(Scene const& scene) const
{

}

void UI::render_present() const
{
    SDL_RenderPresent(ren_);
}

}
