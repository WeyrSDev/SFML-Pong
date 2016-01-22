#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Blackboard.hpp"
#include <engine/FpsDisplay.hpp>
#include <engine/StateStack.hpp>
#include <engine/Context.hpp>
#include <engine/ResourceCache.hpp>
#include <engine/Utility.hpp>
#include <engine/LogSystem.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
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
  bool              filterEvent( sf::Event::EventType eventType );

  sf::RenderWindow  mWindow;
  core::LogSystem         mLog;
  std::unique_ptr<core::FpsDisplay> mFpsDisplay;
  TextureCache      mTextures;
  FontCache         mFonts;
  Blackboard        mBBoard;
  core::Context           mContext;
  core::StateStack        mStack;
  sf::Time          mTimeStep;  
};

#endif