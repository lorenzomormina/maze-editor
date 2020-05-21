#include "Grid.h"

#include "constants.h"

void Grid::Draw(Screen& screen) const
{
    SDL_Color color = { 0xe6, 0xe6, 0xe6, SDL_ALPHA_OPAQUE };
    const auto winSize = screen.GetWindow().GetSize();

    //grid
    screen.GetRenderer().SetDrawColor(color);
    for (auto i = offset.x - offset.x / zoomSpriteSize * zoomSpriteSize;
        i < winSize.w; i += zoomSpriteSize)
        screen.GetRenderer().DrawLine(i, 0, i, winSize.h);
    for (auto i = offset.y - offset.y / zoomSpriteSize * zoomSpriteSize;
        i < winSize.h; i += zoomSpriteSize)
        screen.GetRenderer().DrawLine(0, i, winSize.w, i);

    color = { 0xff, 0, 0, SDL_ALPHA_OPAQUE };
    //origin
    screen.GetRenderer().SetDrawColor(color);
    screen.GetRenderer().DrawLine(offset.x, offset.y - zoomSpriteSize, offset.x,
        offset.y + zoomSpriteSize);
    screen.GetRenderer().DrawLine(offset.x - zoomSpriteSize, offset.y,
        offset.x + zoomSpriteSize, offset.y);
}


Grid::Grid(Screen& screen) :
    offset(Vector2(screen.GetWindow().GetWidth() / 2, screen.GetWindow().GetHeight() / 2)),
    mouseDrag(Vector2(MOUSE_DRAG_UNINITIALIZED, MOUSE_DRAG_UNINITIALIZED))
{}

const Vector2& Grid::GetOffset() const
{
    return offset;
}

const Vector2& Grid::GetMouseDrag() const
{
    return mouseDrag;
}
int Grid::GetZoomSpriteSize() const
{
    return zoomSpriteSize;
}
void Grid::SetOffset(const Vector2 offset)
{
    this->offset = offset;
}
void Grid::SetMouseDrag(const Vector2 mouseDrag)
{
    this->mouseDrag = mouseDrag;
}
void Grid::SetZoomSpriteSize(const int zoomSpriteSize)
{
    this->zoomSpriteSize = zoomSpriteSize;
}

void Grid::AddOffset(const Vector2 offset)
{
    this->offset += offset;
}

void Grid::AddZoomSpriteSize(const int zoomSpriteSize)
{
    this->zoomSpriteSize += zoomSpriteSize;
}

Point Grid::GetTileCoordinates(const Point mouse) const
{
    Point tile;
    const auto mouseXp = mouse.x - offset.x;
    const auto mouseYp = mouse.y - offset.y;
    if (mouseXp > 0) {
        if (mouseYp > 0) {
            tile = Point(
                (mouseXp - mouseXp % zoomSpriteSize) / zoomSpriteSize,
                (mouseYp - mouseYp % zoomSpriteSize) / zoomSpriteSize
            );
        }
        else {
            tile = Point(
                (mouseXp - mouseXp % zoomSpriteSize) / zoomSpriteSize,
                (mouseYp - mouseYp % zoomSpriteSize - zoomSpriteSize) / zoomSpriteSize
            );
        }
    }
    else {
        if (mouseYp > 0) {
            tile = Point(
                (mouseXp - mouseXp % zoomSpriteSize - zoomSpriteSize) / zoomSpriteSize,
                (mouseYp - mouseYp % zoomSpriteSize) / zoomSpriteSize

            );
        }
        else {
            tile = Point(
                (mouseXp - mouseXp % zoomSpriteSize - zoomSpriteSize) / zoomSpriteSize,
                (mouseYp - mouseYp % zoomSpriteSize - zoomSpriteSize) / zoomSpriteSize
            );
        }
    }

    return tile;
}
