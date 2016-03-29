# add the code files from this directory to the parent project
# usage set(SOURCE_FILES ${SOURCE_FILES} <your files go here> PARENT_SCOPE)
# PARENT_SCOPE pulls up the variables content to the parent project

set(SOURCE_FILES
  ${SOURCE_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/DataTables.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GameBall.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GameWorld.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Paddle.cpp
  PARENT_SCOPE
  )