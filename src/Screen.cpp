#include "Screen.h"


Screen::Screen() : renderer(window) {}

Renderer& Screen::GetRenderer()
{
    return renderer;
}

Window& Screen::GetWindow()
{
    return window;
}
