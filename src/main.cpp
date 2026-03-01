#include "common.hpp"
#include "window_renderer.hpp"
#include "engine.hpp"

int main() {
    RendererWindow window;

    Engine engine;
    engine.run(&window);

    window.close();
    return 0;
}
