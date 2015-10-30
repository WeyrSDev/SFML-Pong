#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include "Context.hpp"
#include "State.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <map>
#include <functional>
#include <utility>

class StateStack
{
public:
  enum class Action
  {
    PUSH,
    POP,
    CLEAR,
  };

  explicit StateStack( Context& context );

  template <typename T>
  void registerState( States id );

  void handleInput( const sf::Event& event );
  void update( sf::Time dt );
  void render();

  void pushState( States id );
  void popState();
  void clearStates();
  bool isEmpty() const;
  Context* getContext() const;

private:
  State::Ptr createState( States id );
  void applyPendingChanges();

  struct PendingChange
  {
    explicit PendingChange( Action action, States id = States::NONE )
      : action( action )
      , id( id )
    {}

    Action action;
    States id;
  };

  std::vector<State::Ptr> mStates;
  std::vector<PendingChange> mPendingChanges;
  Context* mContext;
  std::map<States, std::function<State::Ptr()>> mFactories;

  StateStack( const StateStack& ) = delete;
  StateStack& operator=( const StateStack& ) = delete;
};


template <typename T>
void StateStack::registerState( States id )
{
  mFactories[ id ] = [ this ]() {
    return std::make_unique<T>( *this );
  };
}

#endif