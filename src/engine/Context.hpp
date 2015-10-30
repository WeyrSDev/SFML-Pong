#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "ResourceIdentifiers.hpp"
#include "Blackboard.hpp"

namespace sf
{
  class RenderWindow;
}

struct Context
{
  Context( sf::RenderWindow& window, TextureCache& textures, FontCache& fonts, Blackboard& bboard )
    : window( &window )
    , textures( &textures )
    , fonts( &fonts )
    , blackboard( &bboard )
  {}

  sf::RenderWindow* window;
  TextureCache* textures;
  FontCache* fonts;
  Blackboard* blackboard;
};

#endif