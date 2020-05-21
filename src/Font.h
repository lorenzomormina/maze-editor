#pragma once

#include <SDL2/SDL_ttf.h>

struct Font
{
    TTF_Font* font = nullptr;

    Font(const char* path, int size)
    {
        font = TTF_OpenFont(path, size);
    }

    ~Font()
    {
        TTF_CloseFont(font);
    }
};