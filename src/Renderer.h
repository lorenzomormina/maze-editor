#pragma once

#include "Texture.h"
#include "Window.h"
#include "Rect.h"

struct SDL_Renderer_Deleter {
    void operator()(struct SDL_Renderer* renderer) const;
};

class Renderer
{
    std::unique_ptr<SDL_Renderer, SDL_Renderer_Deleter> _renderer;

public:

    Renderer();
    Renderer(Window& window);
    SDL_Renderer* Get_() const;
    void Clear() const;
    void Clear(SDL_Color color) const;
    void Present() const;

    void SetDrawColor(SDL_Color color) const;
    void DrawRect(Rect rect, SDL_Color color) const;
    void DrawTexture(Texture& texture, Rect srcRect, Rect dstRect) const;
    void DrawLine(Point p1, Point p2) const;
    void DrawLine(int x1, int y1, int x2, int y2);
    Texture LoadTexture(const std::string& filePath) const;
};