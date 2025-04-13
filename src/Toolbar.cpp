#include "Toolbar.h"

//Toolbar::Toolbar(Screen& screen, TTF_Font* font, ConfirmationPrompt& confPrompt) :
//    tileButtons(iconNames.size()), font(font), confPrompt(confPrompt)
//{
//    const auto size = screen.GetWindow().GetSize();
//    pos.x = 0; pos.y = 0; this->size.w = size.w; this->size.h = 32;
//
//    for (std::vector<std::string>::size_type i = 0; i < iconNames.size(); i++)
//    {
//        const auto iSigned = static_cast<int>(i);
//        const auto* tmp = new IconButton(
//            "resource/sprite/" + iconNames[i] + ".png",
//            iconNames[i],
//            screen.GetRenderer(),
//            Point(pos.x + iSigned * 32, pos.y)
//        );
//        tileButtons[i] = *tmp;
//    }
//
//    clearBtn = TextButton("Clear", screen.GetRenderer(), Point(size.w - 64, 0), font);
//}

void Toolbar::load(Screen& screen, TTF_Font* font)
{
    tileButtons.resize(iconNames.size() );
    this->font = font;
    const auto size = screen.GetWindow().GetSize();
    pos.x = 0; pos.y = 0; this->size.w = size.w; this->size.h = 32;

    for (std::vector<std::string>::size_type i = 0; i < iconNames.size(); i++)
    {
        const auto iSigned = static_cast<int>(i);
        const auto* tmp = new IconButton(
            "resource/sprite/" + iconNames[i] + ".png",
            iconNames[i],
            screen.GetRenderer(),
            Point(pos.x + iSigned * 32, pos.y)
        );
        tileButtons[i] = *tmp;
    }

    clearBtn = TextButton("Clear", screen.GetRenderer(), Point(iconNames.size()*32+10, 0), font);
    // x is 10 pixels away from the last icon
    auto x = clearBtn.GetPosition().x + clearBtn.rectSize.w + 10;
    centerBtn = TextButton("Center", screen.GetRenderer(), Point(x, 0), font);
    x = centerBtn.GetPosition().x + centerBtn.rectSize.w + 10;
    loadBtn = TextButton("Load", screen.GetRenderer(), Point(x, 0), font);
    x = loadBtn.GetPosition().x + loadBtn.rectSize.w + 10;
    saveBtn = TextButton("Save", screen.GetRenderer(), Point(x, 0), font);
    x = saveBtn.GetPosition().x + saveBtn.rectSize.w + 10;
    //saveAsBtn = TextButton("Save As", screen.GetRenderer(), Point(x, 0), font);
    //x = saveAsBtn.GetPosition().x + saveAsBtn.rectSize.w + 10;


    auto surf = TTF_RenderText_Blended(font, "[unsaved]", { 255, 255, 255, 255 });
    auto sdltexture = SDL_CreateTextureFromSurface(screen.GetRenderer().Get_(), surf);
    fileNameTexture = Texture(sdltexture);
    SDL_FreeSurface(surf);

    int w, h;
    SDL_QueryTexture(fileNameTexture.Get_(), nullptr, nullptr, &w, &h);
    fileNamePos.x = x;
    // center the text vertically
    fileNamePos.y = (32 - h) / 2;
    fileNameSize.w = w;
    fileNameSize.h = h;

    playBtn = TextButton("Play", screen.GetRenderer(), Point(x, 0), font);
    const auto playBtnWidth = playBtn.GetRect().w;
    x = size.w - playBtnWidth - 10;
	playBtn.SetPosition(Point(x, 0));
}

void Toolbar::Draw(Screen& screen)
{

    const Rect rect = Rect(pos, size);
    const SDL_Color color = { 169,169,169,255 };

    screen.GetRenderer().DrawRect(rect, color);

    for (auto& i : tileButtons)
    {
        i.Draw(screen);
    }

    clearBtn.Draw(screen);
    centerBtn.Draw(screen);
    loadBtn.Draw(screen);
    saveBtn.Draw(screen);
    saveAsBtn.Draw(screen);
	playBtn.Draw(screen);
    screen.GetRenderer().DrawTexture(fileNameTexture, Rect(), Rect(fileNamePos, fileNameSize));
}


void Toolbar::SetSize(const RectSize size)
{
    this->size.w = size.w; this->size.h = size.h;
}

const std::vector<IconButton>& Toolbar::GetTileButtons() const
{
    return tileButtons;
}

Rect Toolbar::GetRect() const
{
    Rect rect;
    rect.x = pos.x; rect.y = pos.y; rect.w = size.w; rect.h = size.h;
    return rect;
}