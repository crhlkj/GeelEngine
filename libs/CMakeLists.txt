# Опция: использовать локальную, предварительно собранную GLFW
option(USE_LOCAL_GLFW "Использовать локальную библиотеку GLFW" OFF)

# Опция: собирать GLFW статически (только для USE_LOCAL_GLFW)
option(BUILD_GLFW_SHARED "Собирать GLFW как динамическую библиотеку" OFF)

if(USE_LOCAL_GLFW)
    # Проверка наличия локальной директории GLFW
    if(NOT EXISTS "${PROJECT_SOURCE_DIR}/libs/glfw/CMakeLists.txt")
        message(FATAL_ERROR "USE_LOCAL_GLFW=ON, но директория '${PROJECT_SOURCE_DIR}/libs/glfw' не содержит исходный код GLFW.")
    endif()

    # Собираем GLFW внутри проекта — гарантирует совместимость ABI и корректные системные зависимости.
    add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glfw glfw)

else()
    # Автоматическая загрузка и сборка GLFW через FetchContent
    include(FetchContent)

    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.4
        GIT_SHALLOW    TRUE
    )

    # Отключаем ненужные компоненты из deps/ (как рекомендовано в документации)
    # Это ускоряет сборку и избегает ложных срабатываний при поиске зависимостей.
    set(GLFW_BUILD_EXAMPLES   OFF CACHE BOOL "Собирать примеры программ GLFW" FORCE)
    set(GLFW_BUILD_TESTS      OFF CACHE BOOL "Собирать тестовые программы GLFW" FORCE)
    set(GLFW_BUILD_DOCS       OFF CACHE BOOL "Собирать документацию GLFW" FORCE)
    set(GLFW_INSTALL          OFF CACHE BOOL "Генерировать цель установки" FORCE)

    # Важно: BUILD_SHARED_LIBS унаследуется от родительского проекта, если не переопределено выше

    FetchContent_MakeAvailable(glfw)
endif()

# --- 

# Опция: использовать локальную, предварительно собранную ImGui
option(USE_LOCAL_IMGUI "Используйте локальную библиотеки ImGui" OFF)

# Опция: собирать ImGui статически (только для USE_LOCAL_IMGUI)
option(BUILD_IMGUI_SHARED "Собирать ImGui как как общую библиотеку." OFF)

if(USE_LOCAL_IMGUI)
    # Локальная сборка ImGui - полный контроль над исходным кодом
    set(IMGUI_SOURCES
        ${PROJECT_SOURCE_DIR}/libs/imgui/imgui.cpp
        ${PROJECT_SOURCE_DIR}/libs/imgui/imgui_demo.cpp
        ${PROJECT_SOURCE_DIR}/libs/imgui/imgui_draw.cpp
        ${PROJECT_SOURCE_DIR}/libs/imgui/imgui_tables.cpp
        ${PROJECT_SOURCE_DIR}/libs/imgui/imgui_widgets.cpp
        ${PROJECT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_glfw.cpp
        ${PROJECT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_opengl3.cpp
    )

    # ПРОВЕРКА: Убедитесь, что все файлы существуют
    foreach(source_file ${IMGUI_SOURCES})
        if(NOT EXISTS "${source_file}")
            message(WARNING "Файл ImGui не найден: ${source_file}\n"
                "Убедитесь, что ImGui находится в libs/imgui/")
        endif()
    endforeach()

    if(BUILD_IMGUI_SHARED)
        add_library(imgui SHARED ${IMGUI_SOURCES})
    else()
        add_library(imgui STATIC ${IMGUI_SOURCES})
    endif()

    target_include_directories(imgui 
        PUBLIC
            ${PROJECT_SOURCE_DIR}/libs/imgui
            ${PROJECT_SOURCE_DIR}/libs/imgui/backends
        PRIVATE
            ${GLFW_SOURCE_DIR}/include
    )
endif()

# Опция: собирать GLAD  статическической
option(BUILD_GLAD_SHARED "Собирать GLAD как как общую библиотеку." OFF)

if(BUILD_GLAD_SHARED)
    add_library(glad SHARED
        ${PROJECT_SOURCE_DIR}/libs/glad/src/glad.c
    )
else()
    add_library(glad STATIC
        ${PROJECT_SOURCE_DIR}/libs/glad/src/glad.c
    )
endif()

target_include_directories(glad PUBLIC 
    ${PROJECT_SOURCE_DIR}/libs/glad/include
)
