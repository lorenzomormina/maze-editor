#pragma once
#include <memory>
#include <string>
#include <SDL2/SDL_render.h>
#include "Vector2.h"

struct SDL_Window_Deleter {
    void operator()(SDL_Window* window) const;
};

class Window
{
    std::unique_ptr<SDL_Window, SDL_Window_Deleter> _window;
    RectSize size;

public:
    Window();
    SDL_Window* Get_() const;

    RectSize GetSize() const;
    int GetWidth() const;
    int GetHeight() const;
    void SetTitle(const std::string& title) const;
    void SetSize(RectSize size) const;
    void Show() const;
    void UpdateSize();
};