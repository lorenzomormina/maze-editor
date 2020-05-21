#include "Vector2.h"

Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(const int x, const int y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(this->x + other.x, this->y + other.y);
}

void Vector2::operator+=(const Vector2& other)
{
    *this = *this + other;
}

RectSize::RectSize() :
    w(0), h(0) {}

RectSize::RectSize(const int w, const int h) :
    w(w), h(h) {}
