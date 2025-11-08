cmake_minimum_required(VERSION 4.1.2)
project(Geel VERSION 0.1.0)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_subdirectory(libs)

find_package(OpenGL REQUIRED)
# find_package(Vulkan REQUIRED) Времмено отключено = Основа OpenGL

file(GLOB GEEL_FILES 
    # Главные файлы движка
    # Управление, добавление объектов и т.д.
    src/*.cpp
    src/core/*.cpp

    # Дополнительные утелиты которые могут пригодиться
    # При использовании движка
    tools/*.cpp
)
add_executable(${PROJECT_NAME} ${GEEL_FILES})

target_link_libraries(Geel PRIVATE 
    glfw
    glad
    OpenGL::GL 
    # Vulkan::Vulkan 
)