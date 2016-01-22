#ifndef CORE_CONTEXT_HPP
#define CORE_CONTEXT_HPP

#include <game/ResourceIdentifiers.hpp>

struct Blackboard;
namespace sf
{
  class RenderWindow;
}

namespace core
{
  class LogSystem;  

  struct Context
  {
    Context( sf::RenderWindow& window, TextureCache& textures, FontCache& fonts,
             Blackboard& bboard, LogSystem& log )
      : window( &window )
      , textures( &textures )
      , fonts( &fonts )
      , blackboard( &bboard )
      , log( &log )
    {}

    sf::RenderWindow*   window;
    TextureCache*       textures;
    FontCache*          fonts;
    Blackboard*         blackboard;
    LogSystem*          log;
  };

} // end namespace core
#endif