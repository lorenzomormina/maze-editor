#pragma once

#include <SDL2/SDL_rect.h>

struct Vector2
{
    int x, y;

    Vector2();
    Vector2(int x, int y);
    Vector2 operator+(const Vector2& other) const;
    void operator+=(const Vector2& other);
    Vector2& operator=(const Vector2& other) = default;
};

typedef Vector2 Point;
typedef Vector2 ivec2;

struct irect {
    int x, y, w, h;

    irect(ivec2 pos, ivec2 size)
    {
        x = pos.x;
        y = pos.y;
        w = size.x;
        h = size.y;
    }

    irect(int x, int y, int w, int h)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    ivec2 pos() const
    {
        return ivec2(x, y);
    }

    ivec2 size() const
    {
        return ivec2(w, h);
    }

    ivec2 pos(int x, int y)
    {
        this->x = x;
        this->y = y;
        return ivec2(x, y);
    }

    ivec2 pos(ivec2 pos)
    {
        this->x = pos.x;
        this->y = pos.y;
        return pos;
    }
};


// deprecated
struct RectSize
{
    int w, h;
    RectSize();
    RectSize(int w, int h);
    RectSize& operator=(const RectSize& other) = default;
};