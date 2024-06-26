#pragma once

#include <SDL2/SDL_hints.h>
#include "Vector2.h"

class Application;

class EventHandler
{

    Application& app;
    Point mouseDown;
    RectSize windowSize;

public:
    EventHandler(Application& app);
    void Handle();
    void OnApplicationStart() const;

protected:
    void OnWindowClose() const;
    void OnWindowResize();
    void OnMouseWheel(Sint32 y) const;
    void OnMouseMotion() const;
    void OnMouseButtonDown(Uint8 button);
    void OnMiddleMouseButtonDown() const;
    void OnMouseButtonUp(Uint8 button) const;
    void OnMiddleMouseButtonUp() const;
    void OnLeftMouseButtonDown();
    void OnLeftMouseButtonUp() const;
    void OnWindowLeave() const;
};
