#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <engine/FpsDisplay.hpp>
#include <engine/Context.hpp>
#include <engine/StateStack.hpp>
#include <engine/ResourceCache.hpp>
#include <engine/Blackboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class Application
{
public:
                    Application();
  void              run();

private:
  void              handleInput();
  void              update();
  void              render();

  sf::RenderWindow  mWindow;
  std::unique_ptr<FpsDisplay> mFpsDisplay;
  TextureCache      mTextures;
  FontCache         mFonts;
  Blackboard        mBBoard;
  Context           mContext;
  StateStack        mStack;
  sf::Time          mTimeStep;
};

#endif