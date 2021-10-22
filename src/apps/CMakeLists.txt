
##########################
### COMMON TO ALL APPS ###
##########################

set(MP_APPS_LINKS
    VendorLib
    PhysicsEngineLib
    RenderLib
    APILib
)

set(MP_APPS_INCDIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#######################
### Main Executable ###
#######################

set(MP_MAIN_NAME MathsPhysique)

set(MP_MAIN_SOURCES
    main.cpp
)

mp_add_executable(${MP_MAIN_NAME}
    SOURCE ${MP_MAIN_SOURCES}
    LINKS ${MP_APPS_LINKS}
    INCLUDE_DIRS ${MP_APPS_INCDIRS}
)

##############################
### Test Spring Executable ###
##############################

set(MP_TestSpring_NAME TestSpring)

set(MP_TestSpring_SOURCES
    testSpring.cpp
)

mp_add_executable(${MP_TestSpring_NAME}
    SOURCE ${MP_TestSpring_SOURCES}
    LINKS ${MP_APPS_LINKS}
    INCLUDE_DIRS ${MP_APPS_INCDIRS}
)
