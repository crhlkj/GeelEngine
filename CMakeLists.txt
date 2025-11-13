cmake_minimum_required(VERSION 4.1.1)
project(Tiny3D)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

# Создание `compile_commands.json` (Решение если не видит заголовочные библиотеки)
option(INCLUDES_PATH "Создать дополнительный файл для определения флагов компиляции и путей включения." ON)

if(INCLUDES_PATH)   
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

add_subdirectory(libs)

find_package(OpenGL REQUIRED)

file(GLOB ENGINE_FILES
    src/*.cpp
    src/core/*.cpp
)

add_executable(Tiny3D ${ENGINE_FILES})

# Проверка, являеться ли сборка проекта отладочной
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(Tiny3D PRIVATE 
        -g # Включить отладочную информацию 
        -O0 # Отключение оптимизации кода
    )
else()
    # Включение флагов для компиляции проекта
    target_compile_options(Tiny3D PRIVATE 
        -O3 # Оптимизация проекта
        -Wall -Wextra -Werror # Отображение предупреждения при компиляции
        -pedantic # Гарантирует соответствие стандартам языка C++
    )
endif()

target_include_directories(Tiny3D PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(Tiny3D PRIVATE OpenGL::GL glfw glad imgui)