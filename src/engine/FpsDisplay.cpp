#include "FpsDisplay.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

///////////////////////////////////////////////////////////////////////////////

class FpsDisplay::Impl
{
public:
  Impl( const sf::Font& font, unsigned int size );
  void update( const sf::Time dt );

  sf::Text mFpsText;
  std::size_t mFrames;
  std::size_t mFps;
  sf::Time mFpsTime;
};

///////////////////////////////////////////////////////////////////////////////

FpsDisplay::Impl::Impl( const sf::Font& font, unsigned int size )
  : mFpsText( "0 fps", font, size )
  , mFrames( 0 )
  , mFps( 0 )
  , mFpsTime( sf::Time::Zero )
{}

///////////////////////////////////////////////////////////////////////////////

void FpsDisplay::Impl::update( const sf::Time dt )
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

///////////////////////////////////////////////////////////////////////////////

FpsDisplay::FpsDisplay( const sf::Font& font, unsigned int size )
  : mImpl( std::make_unique<Impl>( font, size ) )
{}

///////////////////////////////////////////////////////////////////////////////

void FpsDisplay::update( const sf::Time dt )
{
  mImpl->update( dt );
}

///////////////////////////////////////////////////////////////////////////////

void FpsDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  states.transform *= getTransform();
  target.draw( mImpl->mFpsText, states );
}

///////////////////////////////////////////////////////////////////////////////