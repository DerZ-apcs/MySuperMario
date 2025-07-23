#https://github.com/meemknight/raylibCmakeSetup
#Version 1.0.0

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

#! ! ! ! ! ! !
#set this to true to ship the game!
#basically this will change the RESOURCES_PATH to be the local path
#! ! ! ! ! ! !
#DELETE THE OUT FOLDER AFTER CHANGING THIS BECAUSE VISUAL STUDIO DOESN'T SEEM TO RECOGNIZE THIS CHANGE AND REBUILD!
option(PRODUCTION_BUILD "Make this a production build" ON)
#DELETE THE OUT FOLDER AFTER CHANGING THIS BECAUSE VISUAL STUDIO DOESN'T SEEM TO RECOGNIZE THIS CHANGE AND REBUILD!

if(MSVC) 
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
endif()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization

# Ensure Raylib is built as static libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Raylib as static libraries" FORCE)




project(mygame)




#Add raylib, and here you would add other libraries if needed!
add_subdirectory(thirdparty/raylib-5.0)
add_subdirectory(thirdparty/imgui-docking)
add_subdirectory(thirdparty/rlImGui)


# MY_SOURCES is defined to be a list of all the source files for my game 
# DON'T ADD THE SOURCES BY HAND, they are already added with this macro
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")


add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)



if(PRODUCTION_BUILD)
	# setup the ASSETS_PATH macro to be in the root folder of your exe
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") 
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1) 

else()
	# Set the path relative to the executable
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="resources/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0) 

endif()


target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES}  "include/Coin.h" "src/Coin.cpp" "include/Brick.h" "src/Brick.cpp" "include/QuestionBlock.h" "src/QuestionBlock.cpp" "include/Mushroom.h" "src/Mushroom.cpp" "include/PowerItem.h" "src/PowerItem.cpp" "include/Star.h" "src/Star.cpp" "include/Flower.h" "src/Flower.cpp" "include/CoinBlock.h" "src/CoinBlock.cpp" "include/CoinEffect.h" "src/CoinEffect.cpp" "include/NoteBlock.h" "src/NoteBlock.cpp" "include/CloudBlock.h" "src/CloudBlock.cpp" "include/RotatingBlock.h" "src/RotatingBlock.cpp")


if(MSVC) # If using the VS compiler...

	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)


	#YOU CAN REMOVE THE CONSOLE WITH THIS LINE! YOU CAN EVEN DO AN IF PRODUCTION_BUILD TO REMOVE IT ONLY IN PRODUCTION BUILDS
	#set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console
	


endif()

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")



# Link raylib library statically, Here wou would add other libraries!
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE 
	raylib_static imgui rlimgui
)

# Set working directory to the source directory for Visual Studio
if (MSVC)
    set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
endif()