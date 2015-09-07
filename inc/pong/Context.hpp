#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "ResourceIdentifiers.hpp"

namespace sf
{
  class RenderWindow;
}

struct Context
{
  Context( sf::RenderWindow& window, TextureCache& textures, FontCache& fonts )
    : window( &window )
    , textures( &textures )
    , fonts( &fonts )
  {}

  sf::RenderWindow* window;
  TextureCache* textures;
  FontCache* fonts;  
};

#endif