#pragma once

#include "Screen.h"
#include "Vector2.h"


class Grid
{
    Vector2 offset;
    int zoomSpriteSize = 32;
    Vector2 mouseDrag;

public:
    Grid(Screen& screen);
    void Draw(Screen& screen) const;
    const Vector2& GetOffset() const;
    const Vector2& GetMouseDrag() const;
    void AddOffset(Vector2 offset);
    int GetZoomSpriteSize() const;
    void SetOffset(Vector2 offset);
    void SetMouseDrag(Vector2 mouseDrag);
    void SetZoomSpriteSize(int zoomSpriteSize);
    void AddZoomSpriteSize(int zoomSpriteSize);
    Point GetTileCoordinates(Point mouse) const;

    // --
    void Center(RectSize winSize)
    {
        offset = Vector2(winSize.w / 2, winSize.h / 2);
        zoomSpriteSize = 32;
    }
};

