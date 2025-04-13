#pragma once
#include <vector>
#include <SDL2/SDL_ttf.h>

#include "TextButton.h"
#include "Vector2.h"

class PToolbar
{

    Point pos;
    RectSize size;

public:
    void Draw(Screen& screen);
    void SetSize(RectSize size);
    Rect GetRect() const;

    // --
    TTF_Font* font;
    TextButton backBtn;
	TextButton resetBtn;

    PToolbar() {}
    void load(Screen& screen, TTF_Font* font);
};