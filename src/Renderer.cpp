#include "Renderer.h"

#include <SDL2/SDL_image.h>


void SDL_Renderer_Deleter::operator()(struct SDL_Renderer* renderer) const
{
    SDL_DestroyRenderer(renderer);
}


Renderer::Renderer()
{
    _renderer = nullptr;
}

Renderer::Renderer(Window& window)
{
    _renderer = std::unique_ptr<SDL_Renderer, SDL_Renderer_Deleter>(
        SDL_CreateRenderer(
            window.Get_(),
            -1,
            SDL_RENDERER_ACCELERATED
        )
        );
}


SDL_Renderer* Renderer::Get_() const
{
    return _renderer.get();
}

void Renderer::Clear(const SDL_Color color) const
{
    SDL_SetRenderDrawColor(Get_(), color.r, color.g, color.b, color.a);
    SDL_RenderClear(Get_());
}

void Renderer::Clear() const
{
    SDL_RenderClear(Get_());
}

void Renderer::Present() const
{
    SDL_RenderPresent(Get_());
}

void Renderer::SetDrawColor(const SDL_Color color) const
{
    SDL_SetRenderDrawColor(Get_(), color.r, color.g, color.b, color.a);
}

void Renderer::DrawRect(const Rect rect, const SDL_Color color) const
{
    SDL_Rect dest = { rect.x,rect.y, rect.w,rect.h };
    SDL_SetRenderDrawColor(Get_(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(Get_(), &dest);
}

void Renderer::DrawTexture(Texture& texture, Rect srcRect, Rect dstRect) const
{
    SDL_Rect* src_r = nullptr;
    SDL_Rect* dst_r = nullptr;
    
    if (!srcRect.IsTrivial())
    {
        src_r = new SDL_Rect;
        *src_r = { srcRect.x, srcRect.y, srcRect.w, srcRect.h };
    }

    if (!dstRect.IsTrivial())
    {
        dst_r = new SDL_Rect;
        *dst_r = { dstRect.x, dstRect.y, dstRect.w, dstRect.h };
    }

    SDL_RenderCopy(Get_(), texture.Get_(), src_r, dst_r);

    delete src_r; delete dst_r;
}


void Renderer::DrawLine(const Point p1, const Point p2) const
{
    SDL_RenderDrawLine(Get_(), p1.x, p1.y, p2.x, p2.y);
}

void Renderer::DrawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(Get_(), x1, y1, x2, y2);
}

Texture Renderer::LoadTexture(const std::string& filePath) const
{
    return Texture(filePath, *this);
}
