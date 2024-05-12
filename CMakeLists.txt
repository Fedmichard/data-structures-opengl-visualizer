cmake_minimum_required(VERSION 3.23)
add_compile_definitions(GL_SILENCE_DEPRECATION=-Wdeprecated-declarations)
add_link_options(/NODEFAULTLIB:MSVCRT)
project(visual_simulator_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(dependencies/GLFW/include)
link_directories(dependencies/GLFW/lib-vc2022)

add_executable(visual_simulator_cpp src/main.cpp)

target_link_libraries(visual_simulator_cpp glfw3.lib)
target_link_libraries(visual_simulator_cpp
    opengl32.lib
)