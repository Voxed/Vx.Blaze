add_library(VxBlazeGLTF GLTFLoader.cpp GLTFLoader.h)
target_sources(VxBlazeGLTF PRIVATE ThirdParty/json.hpp ThirdParty/stb_image.h ThirdParty/stb_image_write.h ThirdParty/tiny_gltf.h)

target_link_libraries(VxBlazeGLTF VxBlaze)