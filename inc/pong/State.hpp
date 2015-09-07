#ifndef STATE_HPP
#define STATE_HPP

#include "StateIdentifiers.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <memory>

class StateStack;
struct Context;

class State
{
public:
  typedef std::unique_ptr<State> Ptr;

  explicit      State( StateStack& stack );
  virtual       ~State();
  virtual bool  handleInput( const sf::Event& event ) = 0;
  virtual bool  update( sf::Time dt ) = 0;
  virtual void  render() = 0;

protected:
  void          requestStackPush( States id );
  void          requestStackPop();
  void          requestStackClear();
  Context*      getContext() const;

private:
  StateStack*   mStack;
};

#endif