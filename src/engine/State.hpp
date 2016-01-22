#ifndef CORE_STATE_HPP
#define CORE_STATE_HPP

#include <states/StateIdentifiers.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <memory>

namespace core
{

class StateStack;
struct Context;

class State
{
public:
  typedef std::unique_ptr<State> Ptr;

  explicit      State( StateStack& stack, States id );
  virtual       ~State() = default;
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
  States        mId;

  State( const State& ) = delete;
  State& operator=( const State& ) = delete;
};

} // end namespace core
#endif