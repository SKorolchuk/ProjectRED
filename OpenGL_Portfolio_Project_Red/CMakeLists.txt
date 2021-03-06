# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (ProjectRED)

set(Boost_INCLUDE_DIR 
	external/boost_1_53_0/)

find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(Boost COMPONENTS REQUIRED)

# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

cmake_minimum_required(VERSION 2.8)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	${OPENAL_LIBRARY}
	GLFW_276
	GLEW_190
)

include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-2.7.6/include/
	external/glm-0.9.4.0/
	external/glew-1.9.0/include/
	${Boost_INCLUDE_DIR}
	${OPENAL_INCLUDE_DIR}
	.
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# Project RED
add_executable(src
	src/main.cpp
	src/main.hpp
	src/Common/shader.cpp
	src/Common/shader.hpp
	src/Common/controls.cpp
	src/Common/controls.hpp
	src/Common/texture.cpp
	src/Common/texture.hpp
	src/Common/objloader.cpp
	src/Common/objloader.hpp
	src/Common/vboindexer.cpp
	src/Common/vboindexer.hpp
	src/Common/quaternion_utils.cpp
	src/Common/quaternion_utils.hpp
	src/Common/tangentspace.cpp
	src/Common/tangentspace.hpp
	src/Common/text2D.cpp
	src/Common/text2D.hpp
	src/Bootstrap/Bootstrapper.cpp
	src/Bootstrap/Bootstrapper.hpp
	src/Bootstrap/IInitializable.hpp
	src/Bootstrap/World.cpp
	src/Bootstrap/World.hpp
	src/Graphics/GraphicsManager.cpp
	src/Graphics/GraphicsManager.hpp
	src/Graphics/IGraphics.hpp
	src/Logic/Game.cpp
	src/Logic/Game.hpp
	src/Logic/IGame.hpp
	src/Logic/GameTime.cpp
	src/Logic/GameTime.hpp
	src/Logic/GameObject.cpp
	src/Logic/GameObject.hpp
	src/Sound/ISoundManager.hpp
	src/Sound/ITrack.hpp
	src/Sound/SoundManager.cpp
	src/Sound/SoundManager.hpp
	src/Sound/Track.cpp
	src/Sound/Track.hpp
	src/Input/IDeviceManager.hpp
	src/Input/InputManager.cpp
	src/Input/InputManager.hpp
)
target_link_libraries(src
	${ALL_LIBS}
	ANTTWEAKBAR_116_OGLCORE_GLFW
)

# Project RED example
add_executable(example
	example/main.cpp
	example/main.hpp
	src/Common/shader.cpp
	src/Common/shader.hpp
	src/Common/controls.cpp
	src/Common/controls.hpp
	src/Common/texture.cpp
	src/Common/texture.hpp
	src/Common/objloader.cpp
	src/Common/objloader.hpp
	src/Common/vboindexer.cpp
	src/Common/vboindexer.hpp
	src/Common/quaternion_utils.cpp
	src/Common/quaternion_utils.hpp
	src/Common/tangentspace.cpp
	src/Common/tangentspace.hpp
	src/Common/text2D.cpp
	src/Common/text2D.hpp
	src/Bootstrap/Bootstrapper.cpp
	src/Bootstrap/Bootstrapper.hpp
	src/Bootstrap/IInitializable.hpp
	src/Bootstrap/World.cpp
	src/Bootstrap/World.hpp
	src/Graphics/GraphicsManager.cpp
	src/Graphics/GraphicsManager.hpp
	src/Graphics/IGraphics.hpp
	src/Logic/Game.cpp
	src/Logic/Game.hpp
	src/Logic/IGame.hpp
	src/Logic/GameTime.cpp
	src/Logic/GameTime.hpp
	src/Logic/GameObject.cpp
	src/Logic/GameObject.hpp
	src/Sound/ISoundManager.hpp
	src/Sound/ITrack.hpp
	src/Sound/SoundManager.cpp
	src/Sound/SoundManager.hpp
	src/Sound/Track.cpp
	src/Sound/Track.hpp
	src/Input/IDeviceManager.hpp
	src/Input/InputManager.cpp
	src/Input/InputManager.hpp
	example/Bootstrap/ExtendedWorld.cpp
	example/Bootstrap/ExtendedWorld.hpp	
	example/Shaders/ColorFragmentShader.glsl  
	example/Shaders/ShadowMappingvertex.glsl      
	example/Shaders/StandardShadingfragment.glsl
	example/Shaders/DepthRTTfragment.glsl         
	example/Shaders/SimpleFragmentShader.glsl
	example/Shaders/StandardShadingvertex.glsl
	example/Shaders/DepthRTTvertex.glsl          
	example/Shaders/SimpleTexturefragment.glsl        
	example/Shaders/StandardTransparentShadingfragment.glsl
	example/Shaders/NormalMappingfragment.glsl          
	example/Shaders/SimpleTransformvertex.glsl           
	example/Shaders/TextVertexShaderfragment.glsl
	example/Shaders/NormalMappingvertex.glsl           
	example/Shaders/SimpleVertexShader.glsl           
	example/Shaders/TextVertexShadervertex.glsl
	example/Shaders/Passthroughvertex.glsl               
	example/Shaders/SingleColorfragment.glsl               
	example/Shaders/TextureFragmentShaderLODfragment.glsl
	example/Shaders/ShadowMapping_SimpleVersionfragment.glsl 
	example/Shaders/StandardShadingRTTfragment.glsl         
	example/Shaders/TextureFragmentShaderfragment.glsl
	example/Shaders/ShadowMapping_SimpleVersionvertex.glsl  
	example/Shaders/StandardShadingRTTvertex.glsl           
	example/Shaders/TransformVertexShadervertex.glsl
	example/Shaders/ShadowMappingfragment.glsl         
	example/Shaders/StandardShading_WithSyntaxErrorsfragment.glsl 
	example/Shaders/WobblyTexturefragment.glsl
)
target_link_libraries(example
	${ALL_LIBS}
	ANTTWEAKBAR_116_OGLCORE_GLFW
)


# Xcode and Visual working directories
set_target_properties(src PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")
create_target_launcher(src WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/")

set_target_properties(src PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/example/")
create_target_launcher(src WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/example/")


SOURCE_GROUP(Common REGULAR_EXPRESSION ".*/src/Common/.*" )
SOURCE_GROUP(Bootstrap REGULAR_EXPRESSION ".*/src/Bootstrap/.*|.*/example/Bootstrap/.*" )
SOURCE_GROUP(Graphics REGULAR_EXPRESSION ".*/src/Graphics/.*" )
SOURCE_GROUP(Logic REGULAR_EXPRESSION ".*/src/Logic/.*" )
SOURCE_GROUP(Sound REGULAR_EXPRESSION ".*/src/Sound/.*" )
SOURCE_GROUP(Input REGULAR_EXPRESSION ".*/src/Input/.*" )
SOURCE_GROUP(Shaders REGULAR_EXPRESSION ".*/example/Shaders/.*")


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
add_custom_command(
   TARGET src POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/src${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)
add_custom_command(
   TARGET example POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/example${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/example/"
)

elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

