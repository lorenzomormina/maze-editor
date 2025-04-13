#pragma once
#include <string>
#include <SDL2/SDL_ttf.h>

#include "Screen.h"


class TextButton
{
    std::string icon;
    std::string name;
    Point pos;
    RectSize size;
    bool pushed = false;

public:

    TextButton();
    TextButton(const std::string& name, Renderer& renderer, Point pos, TTF_Font* font);
    void SetPosition(Point pos);
    Point GetPosition() const;
    void Draw(Screen& screen);
    const std::string& GetName() const;
    bool IsPointInside(Point p) const;
    bool IsPushed() const;
    void Push();
    void Unpush();
	RectSize GetRect() const;

    // --
    Texture texture;
    TTF_Font* font;
    RectSize rectSize;
    void init(const std::string& name, Renderer& renderer, Point pos, TTF_Font* font)
    {
        this->name = name;
        this->pos = pos;
        this->font = font;

        auto surf = TTF_RenderText_Blended(font, name.c_str(), { 255, 255, 255, 255 });
        auto sdltexture = SDL_CreateTextureFromSurface(renderer.Get_(), surf);
        texture = Texture(sdltexture);
        SDL_FreeSurface(surf);

        SDL_QueryTexture(texture.Get_(), nullptr, nullptr, &size.w, &size.h);
        rectSize.w = size.w + 10;
        rectSize.h = 32;
    }
};
