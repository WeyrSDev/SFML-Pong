#include "MusicPlayer.hpp"

MusicPlayer::MusicPlayer()
  : mMusic()
  , mMusicFiles()
  , mVolume( 100u )
{
  // SIC adding files in the player class itself couples it with the content
  // music files must be stored outside the player and only be referenced here
  //mMusicFiles[ Music::MENU_THEME ] = "";
  //mMusicFiles[ Music::GAME_THEME ] = "";

}

void MusicPlayer::play( Music theme )
{
  std::string file = mMusicFiles[ theme ];

  if( !mMusic.openFromFile( file ) ) {
    throw std::runtime_error( "" );
  }

  mMusic.setVolume( mVolume );
  mMusic.setLoop( true );
  mMusic.play();
}

void MusicPlayer::stop()
{
  mMusic.stop();
}

void MusicPlayer::pause()
{
  mMusic.pause();
}

void MusicPlayer::resume()
{
  mMusic.play();
}

void MusicPlayer::setVolume( const float volume )
{
  mVolume = volume;
}