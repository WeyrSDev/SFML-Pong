#include "TextMenu.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <cassert>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////

class TextMenu::Impl
{
public:
  Impl( sf::Font& font, unsigned int textSize, unsigned int space,
        TextMenu::Alignment alignment, sf::Color baseColor,
        sf::Color highlightColor );

  void ensureGeometryUpdate();
  void updateMenuText();

  std::vector<sf::Text>   mEntries;
  sf::Font&               mFont;
  unsigned int            mTextSize;
  unsigned int            mSpacing;
  TextMenu::Alignment     mAlignment;
  std::size_t             mIndex;
  sf::FloatRect           mBounds;
  bool                    mGeometryNeedUpdate;
  sf::Color               mBaseColor;
  sf::Color               mHighlightColor;
};

///////////////////////////////////////////////////////////////////////////////

TextMenu::Impl::Impl( sf::Font& font, unsigned int textSize, unsigned int space,
                      TextMenu::Alignment alignment, sf::Color baseColor,
                      sf::Color highlightColor )
  : mEntries()
  , mFont( font )
  , mTextSize( textSize )
  , mSpacing( space )
  , mAlignment( alignment )
  , mIndex( 0 )
  , mBounds()
  , mGeometryNeedUpdate( false )
  , mBaseColor( baseColor )
  , mHighlightColor( highlightColor )
{}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::Impl::ensureGeometryUpdate()
{
  if( !mGeometryNeedUpdate ) {
    return;
  }
  mGeometryNeedUpdate = false;

  // calculate new bounding rectangle
  mBounds = sf::FloatRect();
  mBounds.top = 0.f;
  mBounds.left = 0.f;

  // all entries * text size + ( all entries - 1 ) * spacing = total y-size
  auto numItem = static_cast<float>( mEntries.size() );
  mBounds.height = numItem * static_cast<float>( mTextSize )
    + ( numItem - 1.f ) * static_cast<float>( mSpacing );

  // cycle through all entries and measure their width
  // to find the biggest one --> total x size
  auto maxXSize { 0.f };
  for( const auto& entry : mEntries ) {
    auto xSize = entry.getLocalBounds().width;
    if( xSize > maxXSize ) {
      maxXSize = xSize;
    }
  }
  mBounds.width = maxXSize;
    
  std::size_t i { 0 };
  for( auto& entry : mEntries ) {
    auto lBounds = entry.getLocalBounds();
    float xOrigin { 0.f };
    float xPos { 0.f };

    if( mAlignment == TextMenu::Alignment::LEFT ) {
      xOrigin = 0.f;
      xPos = 0.f;
    } else if( mAlignment == TextMenu::Alignment::CENTER ) {
      xOrigin = lBounds.width / 2.f;
      xPos = mBounds.width / 2.f;
    } else if( mAlignment == TextMenu::Alignment::RIGHT ) {
      xOrigin = lBounds.width;
      xPos = mBounds.width;
    }

    entry.setOrigin( xOrigin, 0.f );
    entry.setPosition( xPos , static_cast<float>( i * 
                       ( mTextSize + mSpacing ) ) );
    ++i;
  }

  updateMenuText();
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::Impl::updateMenuText()
{
  if( mEntries.empty() ) {
    return;
  }

  for( auto& entry : mEntries ) {
    entry.setColor( mBaseColor );
  }

  mEntries[ mIndex ].setColor( mHighlightColor );
}

// end private implemenation
///////////////////////////////////////////////////////////////////////////////

TextMenu::TextMenu( sf::Font & font, unsigned int textSize, unsigned int space,
                    Alignment alignment, sf::Color baseColor,
                    sf::Color highlightColor )

  : mImpl( std::make_unique<TextMenu::Impl>( font, textSize, space,
           alignment, baseColor, highlightColor ) )
{}

///////////////////////////////////////////////////////////////////////////////

TextMenu::~TextMenu()
{}

///////////////////////////////////////////////////////////////////////////////

int TextMenu::handleInput( const sf::Event & event )
{
  if( event.type == sf::Event::KeyReleased ) {
    if( event.key.code == sf::Keyboard::Return ) {
      return mImpl->mIndex;
    }

    if( event.key.code == sf::Keyboard::Up ) {
      if( mImpl->mIndex > 0 ) {
        --mImpl->mIndex;
      } else {
        mImpl->mIndex = mImpl->mEntries.size() - 1;
      }
      mImpl->updateMenuText();
    }

    if( event.key.code == sf::Keyboard::Down ) {
      if( mImpl->mIndex < mImpl->mEntries.size() - 1 ) {
        ++mImpl->mIndex;
      } else {
        mImpl->mIndex = 0;
      }
      mImpl->updateMenuText();
    }
  }
  
  return -1;
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::update( const sf::Time dt )
{
  // this method could be used for visual effects
  // e.g. animated icons for selected menu entry
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::add( const sf::String entry )
{
  // make sure string ist not empty
  assert( entry != "" );

  sf::Text text( entry, mImpl->mFont, mImpl->mTextSize );
  mImpl->mEntries.push_back( std::move( text ) );

  mImpl->mGeometryNeedUpdate = true;
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::setTextSize( const unsigned int size )
{
  mImpl->mTextSize = size;
}

///////////////////////////////////////////////////////////////////////////////

unsigned int TextMenu::getTextSize() const
{
  return mImpl->mTextSize;
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::setSpacing( const unsigned int space )
{
  mImpl->mSpacing = space;
}

///////////////////////////////////////////////////////////////////////////////

unsigned int TextMenu::getSpacing() const
{
  return mImpl->mSpacing;
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::setAlignment( const Alignment alignment )
{
  mImpl->mAlignment = alignment;
}

///////////////////////////////////////////////////////////////////////////////

TextMenu::Alignment TextMenu::getAlignment() const
{
  return mImpl->mAlignment;
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::setBaseColor( const sf::Color base )
{
  mImpl->mBaseColor = base;
}

///////////////////////////////////////////////////////////////////////////////

sf::Color TextMenu::getBaseColor() const
{
  return mImpl->mBaseColor;
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::setHighlightColor( const sf::Color highlight )
{
  mImpl->mHighlightColor = highlight;
}

///////////////////////////////////////////////////////////////////////////////

sf::Color TextMenu::getHighlightColor() const
{
  return mImpl->mHighlightColor;
}

///////////////////////////////////////////////////////////////////////////////

sf::FloatRect TextMenu::getLocalBounds() const
{
  mImpl->ensureGeometryUpdate();

  return mImpl->mBounds;
}

///////////////////////////////////////////////////////////////////////////////

sf::FloatRect TextMenu::getGlobalBounds() const
{
  return getTransform().transformRect( getLocalBounds() );  
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
  // if no menu entries, abort drawing early
  if( mImpl->mEntries.empty() ) {
    return;
  }

  // make sure geometry is up-to-date
  mImpl->ensureGeometryUpdate();

  // get and apply global transformations and draw all menu entries
  states.transform *= getTransform();
  for( const auto& entry : mImpl->mEntries ) {
    target.draw( entry, states );
  }
}

///////////////////////////////////////////////////////////////////////////////