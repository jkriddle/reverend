#include "Engine.h"

const int Engine::TILE_SIZE = 32;
bool Engine::m_isRunning = true;

int Engine::getScreenHeight() {
    return 640;
}

int Engine::getScreenWidth() {
    return 640;
}

bool Engine::isRunning() {
    return Engine::m_isRunning;
}

void Engine::stop() {
    Engine::m_isRunning = false;
}
