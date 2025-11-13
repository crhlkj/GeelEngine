#include "Geel.h"
using namespace std;

int main(void)
{
    try
    {
        auto window = std::make_unique<Window>(1280, 720, "Geel Engine");

        if (!window->gladInit()) {
            throw std::runtime_error("Failed to initialize GLAD");
            return -1;
        }
        
        glViewport(0, 0, window->getWidth(), window->getHeight());

        while (!window->shouldClose()) {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window->getWindow());
            glfwPollEvents();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
