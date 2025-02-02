#include "game.hh"

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include "ui.hh"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    G(argc, argv);  // initialize game

    SDL_SetAppMetadata(G().name().c_str(), G().version().c_str(), G().app_identifier().c_str());

    if (!SDL_Init(SDL_INIT_VIDEO))
        return SDL_APP_FAILURE;

    U();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    return const_cast<gb::UI&>(U()).event(event);
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    const_cast<gb::Game&>(G()).update();

    gb::Scene scene = U().create_scene();
    U().render_scene(scene);
    U().render();
    U().render_present();
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    const_cast<gb::Game&>(G()).before_quit();
}