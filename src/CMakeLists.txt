
set(MP_EXE_NAME MathsPhysique)

# build libs (order is important)
add_subdirectory(vendor)
add_subdirectory(PhysicsEngine)
add_subdirectory(Render)
add_subdirectory(API)

# build apps
add_subdirectory(apps)

message("{MP_INC_DIRS} ${MP_INC_DIRS}")
