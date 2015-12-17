#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <game/ResourceIdentifiers.hpp>

namespace sf
{
  class RenderWindow;
}

namespace util
{
  class Log;
}

struct Blackboard;

struct Context
{
  Context( sf::RenderWindow& window, TextureCache& textures, FontCache& fonts,
           Blackboard& bboard, util::Log& log )
    : window( &window )
    , textures( &textures )
    , fonts( &fonts )
    , blackboard( &bboard )
    , log( &log )
  {}

  sf::RenderWindow* window;
  TextureCache* textures;
  FontCache* fonts;
  Blackboard* blackboard;
  util::Log* log;
};

#endif