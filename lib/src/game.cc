#include "game.hh"

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    Game* game = Game::instance(argc, argv);
    *appstate = (void *) game;

    SDL_SetAppMetadata(game->name().c_str(), game->version().c_str(), game->app_identifier().c_str());

    if (!SDL_Init(SDL_INIT_VIDEO))
        return SDL_APP_FAILURE;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
}