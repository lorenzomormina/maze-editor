#include "SDLManager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDLManager::SDLManager()
{
    SDL_Init(SDL_INIT_VIDEO);
    if (SDL_IsTextInputActive()) SDL_StopTextInput();
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
}

SDLManager::~SDLManager()
{
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}