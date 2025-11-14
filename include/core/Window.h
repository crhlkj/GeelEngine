#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

struct glfwWindowDeleter
{
    void operator()(GLFWwindow *window) const
    {
        if (window)
            glfwDestroyWindow(window);
    }
};

class Window
{
private:
    std::size_t width_, height_;
    std::unique_ptr<GLFWwindow, glfwWindowDeleter> window_;

public:
    Window(std::size_t width, std::size_t height, std::string title);
    ~Window();

    auto setWindowIcons(std::string pathFiles) const;

    bool gladInit() const;

    bool shouldClose() const;

    auto getWidth() const { return width_; }
    auto getHeight() const { return height_; }

    auto getWindow() const { return window_.get(); }
};

#endif // WINDOW_H