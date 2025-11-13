#include "core/Window.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/stb_image.h"

Window::Window(std::size_t width, std::size_t height, std::string title)
    : width(width), height(height), window(nullptr)
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window_ = std::unique_ptr<GLFWwindow, glfwWindowDeleter>(
        glfwCreateWindow(width_, height_, title.data(), nullptr, nullptr));

    if (!window_) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window_.get());
}

Window::~Window()
{
    if (window_)
    {
        glfwDestroyWindow(window_.get());
    }
    glfwTerminate();
}

auto Window::setWindowIcons(std::string pathFiles) const
{
    int width, height, channels;
    std::unique_ptr<unsigned char, decltype(&stbi_image_free)> data(
        stbi_load(pathFiles.c_str(), &width, &height, &channels, 4),
        stbi_image_free);

    if (data)
    {
        GLFWimage images[1];
        images[0].width = width;
        images[0].height = height;
        images[0].pixels = data.get();

        glfwSetWindowIcon(window_.get(), 1, images);

        std::cout << std::format("Icon loaded successfully: {} ({}x{})\n", pathFiles, width, height);
    }
    else
    {
        throw std::runtime_error(std::format("Failed to load icon: {}", pathFiles));
    }
}

bool Window::gladInit() const {
    return gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window.get());
}
