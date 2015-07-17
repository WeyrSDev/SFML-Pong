#include <pong/FpsDisplay.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

FpsDisplay::FpsDisplay()
  : mFont()
  , mFpsText()
  , mFrames( 0 )
  , mFps( 0 )
  , mFpsTime( sf::Time::Zero )
{
  if( !mFont.loadFromFile( "../media/LiberationMono-Regular.ttf " ) ) {
    throw std::runtime_error( "" );
  }

  mFpsText.setFont( mFont );
  mFpsText.setCharacterSize( 12u );
  mFpsText.setString( "0 fps" );
}

void FpsDisplay::update( const sf::Time dt )
{
  mFpsTime += dt;
  mFrames += 1;

  if( mFpsTime > sf::seconds( 1.f ) ) {
    mFps = mFrames;
    mFrames = 0;
    mFpsTime -= sf::seconds( 1.f );
    mFpsText.setString( std::to_string( mFps ) + " fps" );
  }
}

void FpsDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  states.transform *= getTransform();
  target.draw( mFpsText, states );
}