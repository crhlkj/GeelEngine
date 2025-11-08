#include <memory>
#include <stdexcept>

#include "EngineManager.h"

EngineManager::EngineManager() {
    // Initialize the engine
}

EngineManager::initWindow() {
    if (!glfwInit()) {
        
    }
}