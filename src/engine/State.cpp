#include "State.hpp"
#include "StateStack.hpp"
#include "Utility.hpp"
#ifdef _DEBUG
#include <iostream>
#endif

///////////////////////////////////////////////////////////////////////////////

State::State( StateStack& stack, States id )
  : mStack( &stack )
  , mId( id )
{}

///////////////////////////////////////////////////////////////////////////////

State::~State()
{
#ifdef _DEBUG
  //std::cout << "Destroying state " << mStack->getStateName( mId )
  //  << std::endl;
#endif
}

///////////////////////////////////////////////////////////////////////////////

void State::requestStackPush( States id )
{  
#ifdef _DEBUG
  std::cout << "Requested stack push for state " << mStack->getStateName( id )
    << std::endl;
#endif
  mStack->pushState( id );
}

///////////////////////////////////////////////////////////////////////////////

void State::requestStackPop()
{  
#ifdef _DEBUG
  std::cout << "Requested stack pop for state " << mStack->getStateName( mId )
    << std::endl;
#endif
  mStack->popState();
}

///////////////////////////////////////////////////////////////////////////////

void State::requestStackClear()
{  
#ifdef _DEBUG
  std::cout << "Requested stack clear from state " << mStack->getStateName( mId )
    << std::endl;
#endif
  mStack->clearStates();
}

///////////////////////////////////////////////////////////////////////////////

Context* State::getContext() const
{
  return mStack->getContext();
}

///////////////////////////////////////////////////////////////////////////////