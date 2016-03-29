# add the code files from this directory to the parent project
# usage set(SOURCE_FILES ${SOURCE_FILES} <your files go here> PARENT_SCOPE)
# PARENT_SCOPE pulls up the variables content to the parent project

set(SOURCE_FILES
  ${SOURCE_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/CreditState.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GameoverState.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GameState.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MenuState.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PauseState.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/StateIdentifiers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/TitleState.cpp
  PARENT_SCOPE
  )