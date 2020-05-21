#pragma once
#include <memory>
#include <string>
#include <SDL2/SDL_render.h>

#include "Vector2.h"

class Renderer;
void SDL_Texture_Deleter(SDL_Texture* texture);


class Texture
{
    
    std::shared_ptr<SDL_Texture> _texture;
    
public:
    Texture();
    Texture(const std::string& filePath, const Renderer& renderer);
    RectSize GetSize() const;
    SDL_Texture* Get_() const;

    // --
    Texture(SDL_Texture* texture)
    {
        _texture = std::shared_ptr<SDL_Texture>(texture, SDL_Texture_Deleter);
    }
};

