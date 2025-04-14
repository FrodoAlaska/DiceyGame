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
set(DICE_EXE_NAME "dice_will_ya")

set(DICE_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(DICE_LIBS_DIR ${CMAKE_SOURCE_DIR}/libs)

set(DICE_INCLUDES 
  ${DICE_SRC_DIR}
  ${DICE_LIBS_DIR}
  ${DICE_LIBS_DIR}/nikola/nikola/include
  ${DICE_LIBS_DIR}/nikola/libs/glm
)
set(DICE_LIBRARIES nikola)
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

### Linking ###
############################################################
target_include_directories(${DICE_EXE_NAME} PUBLIC BEFORE ${DICE_INCLUDES})
target_link_libraries(${DICE_EXE_NAME} PUBLIC ${DICE_LIBRARIES})
############################################################

### Compiling Options ###
############################################################
target_compile_options(${DICE_EXE_NAME} PUBLIC ${DICE_BUILD_FLAGS})
target_compile_features(${DICE_EXE_NAME} PUBLIC cxx_std_20)
target_compile_definitions(${DICE_EXE_NAME} PUBLIC ${DICE_BUILD_DEFS})
############################################################
