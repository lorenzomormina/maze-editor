#include "IconButton.h"

IconButton::IconButton(const std::string& iconPath, const std::string& name, Renderer& renderer, const Point pos) :
    icon(Texture(iconPath, renderer)),
    name(name),
    pos(pos),
    size(icon.GetSize()) {}

IconButton::IconButton() :
    icon(Texture()),
    name(""),
    pos(Point()),
    size(RectSize()) {}


void IconButton::SetPosition(Point pos)
{
    this->pos = pos;
}

Point IconButton::GetPosition() const
{
    return pos;
}

void IconButton::Draw(Screen& screen)
{
    const auto dRect = Rect(pos, size);
    screen.GetRenderer().DrawTexture(icon, Rect(), dRect);
}

const std::string& IconButton::GetName() const
{
    return name;
}


bool IconButton::IsPointInside(const Point p) const
{
    const SDL_Rect rect = { pos.x, pos.y, size.w, size.h };
    return p.x >= rect.x && p.x < rect.x + rect.w && p.y >= rect.y && p.y <= rect.y + rect.h;
}


bool IconButton::IsPushed() const
{
    return pushed;
}

void IconButton::Push()
{
    pushed = true;
}
void IconButton::Unpush()
{
    pushed = false;
}