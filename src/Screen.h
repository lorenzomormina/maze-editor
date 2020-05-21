#pragma once

#include "Renderer.h"


class Screen
{
    Window window;
    Renderer renderer;

public:

    Screen();
    Renderer& GetRenderer();
    Window& GetWindow();

};