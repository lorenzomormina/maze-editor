#pragma once
#include <vector>
#include <SDL2/SDL_ttf.h>

#include "IconButton.h"
#include "TextButton.h"
#include "ConfirmationPrompt.h"

class Toolbar
{
    std::vector<std::string> iconNames = {
        "start",
        "exit",
        "wall-rock",
        "coin",
        "selected",
        "eraser"
    };
    std::vector<IconButton> tileButtons;

    Point pos;
    RectSize size;

public:
    //Toolbar(Screen& screen, TTF_Font *font, ConfirmationPrompt& confPrompt);
    void Draw(Screen& screen);
    void SetSize(RectSize size);
    const std::vector<IconButton>& GetTileButtons() const;
    Rect GetRect() const;

    // --
    TTF_Font* font;
    TextButton clearBtn;
    TextButton centerBtn;
    TextButton loadBtn;
    TextButton saveBtn;
    TextButton saveAsBtn;
    std::string& fileName;
    Texture fileNameTexture;
    ivec2 fileNamePos;
    RectSize fileNameSize;

    Toolbar(std::string& fileName) : fileName(fileName) {}
    void load(Screen& screen, TTF_Font* font);
    void fileNameChanged(Screen& screen)
    {
        SDL_Surface* surf = TTF_RenderText_Blended(font, fileName.c_str(), { 255, 255, 255, 255 });
        SDL_Texture* sdltexture = SDL_CreateTextureFromSurface(screen.GetRenderer().Get_(), surf);
        fileNameTexture = Texture(sdltexture);
        SDL_FreeSurface(surf);
    }
};