cmake_minimum_required(VERSION 3.20)
project(OpenGLApp)

set(CMAKE_CXX_STANDARD 17)

# GLFW
add_subdirectory(external/glfw)

# GLAD
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# Executable
add_executable(OpenGLApp main.cpp)

# Include dirs
target_include_directories(OpenGLApp PRIVATE
    external/glad/include
    external/glfw/include
)

# Link everything
target_link_libraries(OpenGLApp glfw glad opengl32)