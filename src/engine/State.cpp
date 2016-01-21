#include "State.hpp"
#include "StateStack.hpp"
#include "Utility.hpp"
#include "LogSystem.hpp"

namespace core
{

State::State( StateStack& stack, States id )
  : mStack( &stack )
  , mId( id )
{}

///////////////////////////////////////////////////////////////////////////////

void State::requestStackPush( States id )
{
  //*getContext()->log << core::Logger::Type::DEBUG
  //  << "Requested stack push for state " << mStack->getStateName( id ) << "\n";
  getContext()->log->write( "Requested stack push for state " + mStack->getStateName( id ),
                          LogType::DEBUG );
  mStack->pushState( id );
}

///////////////////////////////////////////////////////////////////////////////

void State::requestStackPop()
{
  getContext()->log->write( "Requested stack pop for state " + mStack->getStateName( mId ),
                          LogType::DEBUG );
  mStack->popState();
}

///////////////////////////////////////////////////////////////////////////////

void State::requestStackClear()
{
  getContext()->log->write( "Requested stack clear from state " + mStack->getStateName( mId ),
                          LogType::DEBUG );
  mStack->clearStates();
}

///////////////////////////////////////////////////////////////////////////////

Context* State::getContext() const
{
  return mStack->getContext();
}

} // end namespace core