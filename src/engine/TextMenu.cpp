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

namespace core
{
///////////////////////////////////////////////////////////////////////////////

class TextMenu::Impl
{
public:
  Impl( sf::Font& font, unsigned int textSize, unsigned int space,
        sf::Event::EventType keyEventType, TextMenu::Alignment alignment,
        sf::Color baseColor, sf::Color highlightColor );

  void ensureGeometryUpdate();
  void updateMenuText();
  int  handleInput( const sf::Event evt );
  void update( sf::Time dt );
  void add( sf::String entry );

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
  sf::Event::EventType    mKeyEventType;
};

///////////////////////////////////////////////////////////////////////////////

TextMenu::Impl::Impl( sf::Font& font, unsigned int textSize, unsigned int space,
                      sf::Event::EventType keyEventType, TextMenu::Alignment alignment,
                      sf::Color baseColor, sf::Color highlightColor )
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
  , mKeyEventType( keyEventType )
{}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::Impl::ensureGeometryUpdate()
{
  // if no update is needed, do nothing
  if( !mGeometryNeedUpdate ) {
    return;
  }
  // mark as updated
  mGeometryNeedUpdate = false;

  // update text size for all menu entries
  for( auto& entry : mEntries ) {
    entry.setCharacterSize( mTextSize );
  }

  // calculate new bounding rectangle
  mBounds = sf::FloatRect();
  mBounds.top = 0.f;
  mBounds.left = 0.f;

  // calculate total y-size
  // all entries * text size + ( all entries - 1 ) * spacing = total y-size
  auto numItem = static_cast<float>( mEntries.size() );
  mBounds.height = numItem * static_cast<float>( mTextSize )
    + ( numItem - 1.f ) * static_cast<float>( mSpacing );

  // calculate total x-size
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

  // set Alignment and origins of every entry
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
    entry.setPosition( xPos, static_cast<float>( i *
                       ( mTextSize + mSpacing ) ) );
    ++i;
  }

  updateMenuText();
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::Impl::updateMenuText()
{
  // if no entries abort
  if( mEntries.empty() ) {
    return;
  }

  // make all entries the base color
  for( auto& entry : mEntries ) {
    entry.setColor( mBaseColor );
  }

  // and then make the selected index the highlight color
  mEntries[ mIndex ].setColor( mHighlightColor );
}

///////////////////////////////////////////////////////////////////////////////

int TextMenu::Impl::handleInput( const sf::Event evt )
{
  if( evt.type == mKeyEventType ) {
    if( evt.key.code == sf::Keyboard::Return ) {
      return mIndex;
    }

    if( evt.key.code == sf::Keyboard::Up ) {
      if( mIndex > 0 ) {
        --mIndex;
      } else {
        mIndex = mEntries.size() - 1;
      }
      updateMenuText();
    }

    if( evt.key.code == sf::Keyboard::Down ) {
      if( mIndex < mEntries.size() - 1 ) {
        ++mIndex;
      } else {
        mIndex = 0;
      }
      updateMenuText();
    }
  }

  return -1;
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::Impl::update( const sf::Time dt )
{
  // This method can be used to add fancy effects to the menu
  // placed inside impl to be changed without the visible class
  // needed to be recompiled
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::Impl::add( const sf::String entry )
{
  // make sure string ist not empty
  assert( entry != "" );

  sf::Text text( entry, mFont, mTextSize );
  mEntries.push_back( std::move( text ) );
  mGeometryNeedUpdate = true;
}

// end private implemenation
///////////////////////////////////////////////////////////////////////////////

TextMenu::TextMenu( sf::Font & font, unsigned int textSize, unsigned int space,
                    sf::Event::EventType keyEventType, Alignment alignment,
                    sf::Color baseColor, sf::Color highlightColor )

  : mImpl( std::make_unique<TextMenu::Impl>( font, textSize, space,
           keyEventType, alignment, baseColor, highlightColor ) )
{}

///////////////////////////////////////////////////////////////////////////////

TextMenu::~TextMenu()
{}

///////////////////////////////////////////////////////////////////////////////

int TextMenu::handleInput( const sf::Event & evt )
{
  return mImpl->handleInput( evt );
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::update( const sf::Time dt )
{
  mImpl->update( dt );
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::add( const sf::String entry )
{
  mImpl->add( entry );
}

///////////////////////////////////////////////////////////////////////////////

void TextMenu::setTextSize( const unsigned int size )
{
  mImpl->mTextSize = size;
  mImpl->mGeometryNeedUpdate = true;
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
  mImpl->mGeometryNeedUpdate = true;
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
  mImpl->mGeometryNeedUpdate = true;
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
  mImpl->mGeometryNeedUpdate = true;
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
  mImpl->mGeometryNeedUpdate = true;
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

} // end namespace core