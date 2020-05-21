#include "Texture.h"

#include <SDL2/SDL_image.h>

#include "Renderer.h"


void SDL_Texture_Deleter(SDL_Texture* texture)
{
    SDL_DestroyTexture(texture);
}

Texture::Texture(): _texture(nullptr) {}

Texture::Texture(const std::string& filePath, const Renderer& renderer)
{
    auto* surface = IMG_Load(filePath.c_str());
    const auto colorKey = SDL_MapRGB(surface->format, 0, 0, 0);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    auto* texture = SDL_CreateTextureFromSurface(renderer.Get_(), surface);
    SDL_FreeSurface(surface);
    _texture = std::shared_ptr<SDL_Texture>(texture,SDL_Texture_Deleter);
}

SDL_Texture* Texture::Get_() const
{
    return _texture.get();
}

RectSize Texture::GetSize() const
{
    int w, h;
    SDL_Texture* t = Get_();;
    SDL_QueryTexture(t, nullptr, nullptr, &w, &h);
    return { w, h };
}
