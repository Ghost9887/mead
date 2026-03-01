#include "window_renderer.hpp"

RendererWindow::RendererWindow() :
        window(nullptr), renderer(nullptr), canvas(nullptr)
{
  
    window = SDL_CreateWindow(
        "Mead", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        0
    );
    if (window == nullptr)
        std::cout << "SDL could not create  window!\n";

    renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED
    );

    if (renderer == nullptr)
        std::cout << "SDL could not create renderer!\n";

    canvas = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );
}

SDL_Renderer* RendererWindow::get_renderer() {
    return renderer;
}

SDL_Texture * RendererWindow::get_canvas() {
  return canvas;
}

RendererWindow::~RendererWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(canvas);
    renderer = nullptr;
    window = nullptr;
    canvas = nullptr;
    SDL_Quit();
}
