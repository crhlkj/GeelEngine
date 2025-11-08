@REM Клонирование библиотек: GLFW и ImGui
@echo off

@REM GLFW
echo Клонируем GLFW с GitHub...
git clone https://github.com/glfw/glfw.git

if %errorlevel% equ 0 (
    echo GLFW успешно клонирована!
) else (
    echo Ошибка клонирования GLFW. Установлен ли Git и добавлен в PATH?
    pause
    exit /b 1
)

@REM ImGui
echo Клонируем ImGui с GitHub...
git clone https://github.com/ocornut/imgui.git

if %errorlevel% equ 0 (
    echo ImGui успешно клонирована!
) else (
    echo Ошибка клонирования ImGui.
    pause
    exit /b 1
)

echo Все библиотеки успешно клонированы!
pause