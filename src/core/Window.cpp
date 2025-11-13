#include "core/Window.h"

Window::Window(std::size_t width, std::size_t height, std::string title)
    : width(width), height(height)
{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
    } 
    glfwTerminate();
}

bool Window::gladInit() const {
    return gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
} 

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window);
}
