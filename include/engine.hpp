#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "common.hpp"
#include "window_renderer.hpp"
#include "brush.hpp"
#include "ui_manager.hpp"

class Engine {
public:
    Engine() = default;
    void run(RendererWindow *window);
};

#endif
