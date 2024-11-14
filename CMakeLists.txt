cmake_minimum_required(VERSION 3.13)
set(project_name SandBox)
project(${project_name})


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") 
set(CMAKE_BUILD_TYPE Debug)
add_executable(${project_name} src/main.cpp src/Render/Shader.cpp)

# settings for glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# add external libraries
add_subdirectory(external/glfw)
add_subdirectory(external/glad)
target_link_libraries(${project_name} glfw Glad)
target_include_directories(${project_name} PRIVATE external/glad/include)
