#pragma once
#include <string>

#include "Screen.h"


class IconButton
{
    Texture icon;
    std::string name;
    Point pos;
    RectSize size;
    bool pushed = false;
    
public:

    IconButton();
    IconButton(const std::string& iconPath, const std::string& name, Renderer& renderer, Point pos);
    void SetPosition(Point pos);
    Point GetPosition() const;
    void Draw(Screen& screen);
    const std::string& GetName() const;
    bool IsPointInside(Point p) const;
    bool IsPushed() const;
    void Push();
    void Unpush();
    
};
