cmake_minimum_required(VERSION 3.13)
set(project_name SandBox)
project(${project_name})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE INTERNAL "")
set(CMAKE_BUILD_TYPE Debug)

# Основной исполняемый файл
add_executable(
  ${project_name} src/main.cpp src/Render/Shader.cpp src/utils/VAO.cpp
  src/utils/VBO.cpp src/utils/EBO.cpp src/utils/Texture.cpp src/Render/Camera.cpp)

# Настройки для GLFW
set(GLFW_BUILD_DOCS
    OFF
    CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES
    OFF
    CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS
    OFF
    CACHE BOOL "" FORCE)
set(GLFW_INSTALL
    OFF
    CACHE BOOL "" FORCE)

# Добавляем внешние библиотеки
add_subdirectory(external/glfw)
add_subdirectory(external/glad)

# Подключаем stb_image как библиотеку
add_library(stb_image STATIC external/stb/stb_image.cpp)
target_include_directories(stb_image
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/stb)

# Подключаем glm (только заголовочные файлы, цели нет)
target_include_directories(${project_name}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/glm)

# Подключаем все внешние библиотеки к проекту SandBox
target_link_libraries(${project_name} PRIVATE glfw Glad stb_image)

# Указываем дополнительные директории заголовков
target_include_directories(${project_name} PRIVATE external/glad/include)
