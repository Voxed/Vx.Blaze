add_executable(Triangle Main.cpp ThirdParty/OBJ_Loader.h ThirdParty/stb_image.h)
target_link_libraries(Triangle PRIVATE VxBlaze VxBlazeGLTF)

find_package(glfw3 REQUIRED)

target_link_libraries(Triangle PUBLIC glfw)