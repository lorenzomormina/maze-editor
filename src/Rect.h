#pragma once
#include <SDL2/SDL_rect.h>

#include "Vector2.h"

struct Rect
{
    int x, y, w, h;
    Rect();
    Rect(int x, int y, int w, int h);
    Rect(Point vertex, RectSize size);
    bool IsTrivial() const;
    SDL_Rect Get_() const;
    bool Contains(Point p) const;

    void update(int x, int y, int w, int h)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }
};


