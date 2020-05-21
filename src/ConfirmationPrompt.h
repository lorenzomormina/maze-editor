#pragma once
#include "Vector2.h"
#include "TextButton.h"

struct ConfirmationPrompt
{
    bool active = false;
    Rect rect;
    Rect textRect;
    Texture prompt;
    TextButton yesBtn;
    TextButton noBtn;

    void setRect(Screen& screen, TTF_Font* font)
    {
        rect.w = 200;
        rect.h = 100;
        const auto size = screen.GetWindow().GetSize();
        rect.x = size.w / 2 - rect.w / 2;
        rect.y = size.h / 2 - rect.h / 2;

        yesBtn.init("Yes", screen.GetRenderer(), { 0, 0 }, font);
        noBtn.init("No", screen.GetRenderer(), { 0, 0 }, font);
        yesBtn.SetPosition({ rect.x + 10, rect.y + rect.h - 40 });
        noBtn.SetPosition({ rect.x + rect.w - 50, rect.y + rect.h - 40 });

        auto surf = TTF_RenderText_Blended(font, "Are you sure?", { 255, 255, 255, 255 });
        auto sdltexture = SDL_CreateTextureFromSurface(screen.GetRenderer().Get_(), surf);
        prompt = Texture(sdltexture);
        SDL_FreeSurface(surf);

        SDL_QueryTexture(prompt.Get_(), nullptr, nullptr, &textRect.w, &textRect.h);
        textRect.x = rect.x + rect.w / 2 - textRect.w / 2;
        textRect.y = rect.y + 10;
    }

    void Draw(Screen& screen)
    {
        if (!active)
            return;

        screen.GetRenderer().DrawRect(rect, { 200, 200, 255, 255 });
        screen.GetRenderer().DrawTexture(prompt, Rect(), textRect);
        yesBtn.Draw(screen);
        noBtn.Draw(screen);
    }
};