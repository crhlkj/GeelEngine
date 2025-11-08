#ifndef ENGINEMANAGER_H
#define ENGINEMANAGER_H

#include <iostream>
#include <GLFW/glfw3.h>

class EngineManager {
    private:
        unsigned int width, height;
        std::string title;

    public:
        void initWindow();
};

#endif // ENGINEMANAGER_H