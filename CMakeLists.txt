cmake_minimum_required(VERSION 3.21)
project(VxBlaze)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_library(VxBlaze Node.cpp Node.h NodeVisitor.h Geometry.cpp Geometry.h OGLVisitor.cpp OGLVisitor.h ShaderManager.cpp ShaderManager.h ResourceManager.cpp ResourceManager.h Camera.cpp Camera.h Group.cpp Group.h ShaderNode.cpp ShaderNode.h Shader.cpp Shader.h TransformNode.cpp TransformNode.h)
target_include_directories(VxBlaze PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(VxBlaze PUBLIC OpenGL::OpenGL GLEW::GLEW glm)

add_subdirectory(Vx.Blaze.GLTF)
add_subdirectory(Samples)