### Project Sources ###
############################################################
set(DICE_SOURCES 
  # Base 
  ${DICE_SRC_DIR}/core/main.cpp
  ${DICE_SRC_DIR}/core/app.cpp

  # Entities
  ${DICE_SRC_DIR}/entities/dice.cpp
)
############################################################

### Final Build ###
############################################################
add_executable(${DICE_EXE_NAME} ${DICE_SOURCES})
############################################################
