#include "StateStack.hpp"
#include "Utility.hpp"
#include "LogSystem.hpp"
#include <cassert>
#include <algorithm>
#ifdef _DEBUG
#include <iostream>
#endif

namespace core
{

///////////////////////////////////////////////////////////////////////////////

StateStack::StateStack( Context& context )
  : mStates()
  , mPendingChanges()
  , mContext( &context )
  , mFactories()
  , mStateStrings( initStateStrings() )
{}

///////////////////////////////////////////////////////////////////////////////

void StateStack::handleInput( const sf::Event& event )
{
  for( auto itr = std::rbegin( mStates ); itr != std::rend( mStates ); ++itr ) {
    if( !( *itr )->handleInput( event ) )
      break;
  }
  applyPendingChanges();
}

///////////////////////////////////////////////////////////////////////////////

void StateStack::update( const sf::Time dt )
{
  for( auto itr = std::rbegin( mStates ); itr != std::rend( mStates ); ++itr ) {
    if( !( *itr )->update( dt ) ) {
      break;
    }
  }
  applyPendingChanges();
}

///////////////////////////////////////////////////////////////////////////////

void StateStack::render()
{
  for( const auto& state : mStates ) {
    state->render();
  }
}

///////////////////////////////////////////////////////////////////////////////

void StateStack::pushState( States id )
{
  mPendingChanges.push_back( PendingChange( Action::PUSH, id ) );
  mContext->log->write( "state changed to " + getStateName( id ), LogType::DEBUG );
}

///////////////////////////////////////////////////////////////////////////////

void StateStack::popState()
{
  mPendingChanges.push_back( PendingChange( Action::POP ) );
}

///////////////////////////////////////////////////////////////////////////////

void StateStack::clearStates()
{
  mPendingChanges.push_back( PendingChange( Action::CLEAR ) );
}

///////////////////////////////////////////////////////////////////////////////

bool StateStack::isEmpty() const
{
  return mStates.empty();
}

///////////////////////////////////////////////////////////////////////////////

Context* StateStack::getContext() const
{
  return mContext;
}

std::string StateStack::getStateName( States id ) const
{
  auto name = mStateStrings.find( id );
  if( name != std::end( mStateStrings ) ) {
    return name->second;
  } else {
    return std::string( "NAME NOT FOUND" );
  }
}

// end public interface
///////////////////////////////////////////////////////////////////////////////

State::Ptr StateStack::createState( States id )
{
  auto found = mFactories.find( id );
  assert( found != mFactories.end() );

  return found->second();
}

///////////////////////////////////////////////////////////////////////////////

void StateStack::applyPendingChanges()
{
  for( const auto& change : mPendingChanges ) {
    switch( change.action ) {
      case Action::PUSH:
        mStates.push_back( createState( change.id ) );
        break;

      case Action::POP:
        mStates.pop_back();
        break;

      case Action::CLEAR:
        mStates.clear();
        break;
    }
  }

  mPendingChanges.clear();
}

///////////////////////////////////////////////////////////////////////////////

} // end namespace core