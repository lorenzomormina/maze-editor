#include "Window.h"

#include "constants.h"

void SDL_Window_Deleter::operator()(SDL_Window* window) const
{
    SDL_DestroyWindow(window);
}

Window::Window() : size({ WINDOW_INITIAL_WIDTH,WINDOW_INITIAL_HEIGHT })
{
    _window = std::unique_ptr<SDL_Window, SDL_Window_Deleter>(
        SDL_CreateWindow(
            "",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            size.w, size.h,
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN
        )
        );
}


SDL_Window* Window::Get_() const
{
    return _window.get();
}

RectSize Window::GetSize() const
{
    RectSize size = { 0,0 };
    SDL_GetWindowSize(Get_(), &size.w, &size.h);
    return size;
}


int Window::GetWidth() const
{
    int w;
    SDL_GetWindowSize(Get_(), &w, nullptr);
    return w;
}

int Window::GetHeight() const
{
    int h;
    SDL_GetWindowSize(Get_(), nullptr, &h);
    return h;
}

void Window::SetTitle(const std::string& title) const
{
    SDL_SetWindowTitle(Get_(), title.c_str());
}

void Window::SetSize(const RectSize size) const
{
    SDL_SetWindowSize(Get_(), size.w, size.h);
}

void Window::Show() const
{
    SDL_ShowWindow(Get_());
}


void Window::UpdateSize()
{
    SDL_GetWindowSize(Get_(), &size.w, &size.h);
}