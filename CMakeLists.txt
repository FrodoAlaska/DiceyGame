cmake_minimum_required(VERSION 3.27)
project(DiceGame)

### Includes ###
############################################################
# This script includes a bunch of platform-specific variables and definitions that
# will be helpful later on.
include(cmake/utils.cmake)
############################################################

### Project Variables ###
############################################################
set(DICE_SRC_DIR ${CMAKE_SOURCE_DIR})
set(DICE_LIBS_DIR ${CMAKE_SOURCE_DIR}/libs)

set(DICE_INCLUDES 
  ${DICE_SRC_DIR}
  ${DICE_LIBS_DIR}
  ${DICE_LIBS_DIR}/nikola/include
)
set(DICE_BUILD_LIBRARIES nikola)
############################################################

### CMake Variables ###
############################################################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
############################################################

### Sub Directories ###
############################################################
add_subdirectory(src)
add_subdirectory(libs/nikola)
############################################################
