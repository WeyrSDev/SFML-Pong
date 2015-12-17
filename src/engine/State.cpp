#include "State.hpp"
#include "StateStack.hpp"
#include "Utility.hpp"

///////////////////////////////////////////////////////////////////////////////

State::State( StateStack& stack, States id )
  : mStack( &stack )
  , mId( id )
{}

///////////////////////////////////////////////////////////////////////////////

void State::requestStackPush( States id )
{  
  //*getContext()->log << util::Logger::Type::DEBUG
  //  << "Requested stack push for state " << mStack->getStateName( id ) << "\n";
  getContext()->log->msg( "Requested stack push for state " + mStack->getStateName( id ),
                          util::LogType::DEBUG );
  mStack->pushState( id );
}

///////////////////////////////////////////////////////////////////////////////

void State::requestStackPop()
{  
  getContext()->log->msg( "Requested stack pop for state " + mStack->getStateName( mId ),
                          util::LogType::DEBUG );
  mStack->popState();
}

///////////////////////////////////////////////////////////////////////////////

void State::requestStackClear()
{  
  getContext()->log->msg( "Requested stack clear from state " + mStack->getStateName( mId ),
                          util::LogType::DEBUG );
  mStack->clearStates();
}

///////////////////////////////////////////////////////////////////////////////

Context* State::getContext() const
{
  return mStack->getContext();
}

///////////////////////////////////////////////////////////////////////////////