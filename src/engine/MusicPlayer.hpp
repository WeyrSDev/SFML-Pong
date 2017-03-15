#ifndef CORE_MUSICPLAYER_HPP
#define CORE_MUSICPLAYER_HPP

#include <SFML/Audio/Music.hpp>
#include <map>

// forward declaring of Music id's decouples player from actual content
// content must be declared and loaded outside of class

namespace core
{

struct Context;

enum class Music : unsigned short;

class MusicPlayer {
public:
  MusicPlayer( Context* context );

  void play( Music theme );

  void stop();

  void pause();

  void resume();

  void setVolume( float volume );

private:
  sf::Music mMusic;
  float mVolume;
  Context* mContext;

  MusicPlayer( const MusicPlayer & ) = delete;
  MusicPlayer &operator=( const MusicPlayer & ) = delete;
};

} // end namespace core
#endif