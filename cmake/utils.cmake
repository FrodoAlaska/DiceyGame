if(WIN32)
  ### Definitions ###
  ###############################
  set(DICE_BUILD_DEFS 
    "WIN32"
    "DICE_PLATFORM_WINDOWS"
    "$<$<CONFIG:Debug>:DEBUG; DICE_BUILD_DEBUG>$<$<CONFIG:Release>:NDEBUG; DICE_BUILD_RELEASE>"
  )
  ###############################
  
  ### Build Flags ### 
  ###############################
  set(DICE_BUILD_FLAGS
    "/W0"
  )
  ###############################
elseif(LINUX) 
  if(CMAKE_BUILD_TYPE STREQUAL "Debug") 
    set(BUILD_FLAGS 
      "DICE_BUILD_DEBUG"
    )
  else()
    set(BUILD_FLAGS 
      "DICE_BUILD_RELEASE"
    )
  endif()

  ### Definitions ###
  ###############################
  set(DICE_BUILD_DEFS 
    "LINUX"
    "DICE_PLATFORM_LINUX"
    ${BUILD_FLAGS}
  )
  ###############################
 
  ### Build Flags ### 
  ###############################
  set(DICE_BUILD_FLAGS
    "-lm" 
    "-w"
  )
  ###############################
endif()
