#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <stdexcept>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Window {
    private:
        GLFWwindow *window;
        std::size_t width, height;

    public:
        Window(std::size_t width, std::size_t height, std::string title);
        ~Window();

        bool gladInit() const;

        bool shouldClose() const;

        auto getWidth() const { return width; }
        auto getHeight() const { return height; }

        GLFWwindow *getWindow() const { return window; }

        
};

#endif // WINDOW_H