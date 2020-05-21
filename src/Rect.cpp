#include "Rect.h"

Rect::Rect()
{
    x = y = w = h = 0;
}

Rect::Rect(int x, int y, int w, int h) :
    x(x), y(y), w(w), h(h) {}

bool Rect::IsTrivial() const
{
    return x == 0 && y == 0 && w == 0 && h == 0;
}
SDL_Rect Rect::Get_() const
{
    return { x, y, w, h };
}

Rect::Rect(const Point vertex, const RectSize size)
{
    x = vertex.x;
    y = vertex.y;
    w = size.w;
    h = size.h;
}

bool Rect::Contains(Point p) const
{
    return p.x >= x && p.x < x + w && p.y >= y && p.y <= y + h;
}
