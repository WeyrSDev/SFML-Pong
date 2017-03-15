#ifndef CORE_CONTEXT_HPP
#define CORE_CONTEXT_HPP

#include <map>

struct Blackboard;
enum class Textures : unsigned short;
enum class Fonts : unsigned short;
enum class Sounds : unsigned short;
enum class Music : unsigned short;

namespace sf
{
  class RenderWindow;
  class Texture;
  class Font;
  class SoundBuffer;
}

namespace core
{
  class LogSystem;
  template <typename Resource, typename Identifier>
  class ResourceCache;
  typedef ResourceCache<sf::Texture, Textures> TextureCache;
  typedef ResourceCache<sf::Font, Fonts> FontCache;
  typedef ResourceCache<sf::SoundBuffer, Sounds> SoundCache;
  typedef std::map<Music, std::string> MusicCache;

  // central engine context
  // holds pointers to all engine subsystems for easy access
  // across all application states
  struct Context
  {
    Context( sf::RenderWindow& window, TextureCache& textures, FontCache& fonts,
             MusicCache& music, Blackboard& bboard, LogSystem& log )
      : window( &window )
      , textures( &textures )
      , fonts( &fonts )
      , music( &music )
      , blackboard( &bboard )
      , log( &log )
    {}

    sf::RenderWindow*   window;
    TextureCache*       textures;
    FontCache*          fonts;
    MusicCache*         music;
    Blackboard*         blackboard;
    LogSystem*          log;
  };

} // end namespace core
#endif