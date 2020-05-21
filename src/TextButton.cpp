#include "TextButton.h"

TextButton::TextButton(const std::string& name, Renderer& renderer, const Point pos, TTF_Font* font) :
    name(name),
    pos(pos),
    size(),
    font(font) {

    auto surf = TTF_RenderText_Blended(font, name.c_str(), { 255, 255, 255, 255 });
    auto sdltexture = SDL_CreateTextureFromSurface(renderer.Get_(), surf);
    texture = Texture(sdltexture);
    SDL_FreeSurface(surf);

    SDL_QueryTexture(texture.Get_(), nullptr, nullptr, &size.w, &size.h);
    rectSize.w = size.w + 10;
    rectSize.h = 32;

}

TextButton::TextButton() :
    name(""),
    pos(Point()),
    size(RectSize()) {}


void TextButton::SetPosition(Point pos)
{
    this->pos = pos;
}

Point TextButton::GetPosition() const
{
    return pos;
}

void TextButton::Draw(Screen& screen)
{
    auto dRect = Rect(pos, rectSize);
    screen.GetRenderer().DrawRect(dRect, { 0, 0, 255, 255 });
    dRect.update(dRect.x + 5, dRect.y + 5, dRect.w - 10, dRect.h - 10);

    screen.GetRenderer().DrawTexture(texture, Rect(), dRect);
}

const std::string& TextButton::GetName() const
{
    return name;
}


bool TextButton::IsPointInside(const Point p) const
{
    const SDL_Rect rect = { pos.x, pos.y, rectSize.w, rectSize.h };
    return p.x >= rect.x && p.x < rect.x + rect.w && p.y >= rect.y && p.y <= rect.y + rect.h;
}


bool TextButton::IsPushed() const
{
    return pushed;
}

void TextButton::Push()
{
    pushed = true;
}
void TextButton::Unpush()
{
    pushed = false;
}