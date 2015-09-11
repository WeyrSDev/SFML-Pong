#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "FpsDisplay.hpp"
#include "Context.hpp"
#include "StateStack.hpp"
#include "ResourceCache.hpp"
#include "ResourceIdentifiers.hpp"
#include "Blackboard.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
public:
                    Application();
  void              run();

private:
  void              handleInput();
  void              update( sf::Time dt );
  void              render();

  sf::RenderWindow  mWindow;
  FpsDisplay        mFpsDisplay;
  TextureCache      mTextures;
  FontCache         mFonts;
  Blackboard        mBBoard;
  Context           mContext;
  StateStack        mStack;
  sf::Time          mTimeStep;
};

#endif