#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

//#include "ResourceIdentifiers.hpp"
#include <SFML/Audio/Music.hpp>
#include <map>

// forward declaring of Music id's decouples player from actual content
// content must be declared and loaded outside of class
enum class Music : unsigned short;

class MusicPlayer
{
public:
  MusicPlayer();
  void play( Music theme );
  void stop();
  void pause();
  void resume();
  void setVolume( float volume );

private:
  sf::Music mMusic;
  std::map<Music, std::string> mMusicFiles;
  float mVolume;

  MusicPlayer( const MusicPlayer& ) = delete;
  MusicPlayer& operator=( const MusicPlayer& ) = delete;
};

#endif