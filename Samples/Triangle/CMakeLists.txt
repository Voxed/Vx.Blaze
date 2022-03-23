add_executable(Triangle Main.cpp ThirdParty/OBJ_Loader.h)
target_link_libraries(Triangle PRIVATE VxBlaze)

find_package(glfw3 REQUIRED)

target_link_libraries(Triangle PUBLIC glfw)