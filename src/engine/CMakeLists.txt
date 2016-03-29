# add the code files from this directory to the parent project
# usage set(SOURCE_FILES ${SOURCE_FILES} <your files go here> PARENT_SCOPE)
# PARENT_SCOPE pulls up the variables content to the parent project

set(SOURCE_FILES
  ${SOURCE_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/Entity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/FpsDisplay.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/LogSystem.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MusicPlayer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/State.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/StateStack.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/TextMenu.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Utility.cpp
  PARENT_SCOPE
  )