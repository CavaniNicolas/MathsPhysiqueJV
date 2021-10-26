
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

##############################
### Main Executable Phase1 ###
##############################

set(MP_MAIN1_NAME mainPhase1)

set(MP_MAIN1_SOURCES
    mainApp1/mainPhase1.cpp
    mainApp1/UserInterface.cpp
)

set(MP_MAIN1_HEADERS
    mainApp1/UserInterface.hpp
)

mp_add_executable(${MP_MAIN1_NAME}
    SOURCE ${MP_MAIN1_SOURCES} ${MP_MAIN1_HEADERS}
    LINKS ${MP_APPS_LINKS}
    INCLUDE_DIRS ${MP_APPS_INCDIRS}
)

###############################
#### Main Executable Phase2 ###
###############################

set(MP_MAIN2_NAME mainPhase2)

set(MP_MAIN2_SOURCES
    mainApp2/mainPhase2.cpp
    mainApp2/UserInterface.cpp
)

set(MP_MAIN2_HEADERS
    mainApp2/UserInterface.hpp
)

mp_add_executable(${MP_MAIN2_NAME}
    SOURCE ${MP_MAIN2_SOURCES} ${MP_MAIN2_HEADERS}
    LINKS ${MP_APPS_LINKS}
    INCLUDE_DIRS ${MP_APPS_INCDIRS}
)


set(MP_MAIN3_NAME testMatrix)

set(MP_MAIN3_SOURCES
    #mainApp3/mainPhase3.cpp
    #mainApp3/UserInterface.cpp
    mainApp3/testMatrix.cpp
)

set(MP_MAIN3_HEADERS
    #mainApp3/UserInterface.hpp
)

mp_add_executable(${MP_MAIN3_NAME}
    SOURCE ${MP_MAIN3_SOURCES} ${MP_MAIN3_HEADERS}
    LINKS ${MP_APPS_LINKS}
    INCLUDE_DIRS ${MP_APPS_INCDIRS}
)

if(BUILD_TESTS)

    ##############################
    ### Test Spring Executable ###
    ##############################

    set(MP_TestSpring_NAME TestSpring)

    set(MP_TestSpring_SOURCES
        testSpring/testSpring.cpp
    )

    mp_add_executable(${MP_TestSpring_NAME}
        SOURCE ${MP_TestSpring_SOURCES}
        LINKS ${MP_APPS_LINKS}
        INCLUDE_DIRS ${MP_APPS_INCDIRS}
    )

    ##############################
    ###  Test Wall Executable  ###
    ##############################

    set(MP_TestWall_NAME TestWall)

    set(MP_TestWall_SOURCES
        testWall/testWall.cpp
    )

    mp_add_executable(${MP_TestWall_NAME}
        SOURCE ${MP_TestWall_SOURCES}
        LINKS ${MP_APPS_LINKS}
        INCLUDE_DIRS ${MP_APPS_INCDIRS}
    )

endif()
