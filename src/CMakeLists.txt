set(DICE_EXE_NAME "dice_will_ya")

### Project Sources ###
############################################################
set(DICE_SOURCES 
  # Base 
  ${DICE_SRC_DIR}/main.cpp
  ${DICE_SRC_DIR}/game.cpp
)
############################################################

### Final Build ###
############################################################
add_executable(${DICE_EXE_NAME} ${DICE_SOURCES})
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
