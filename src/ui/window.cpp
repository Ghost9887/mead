#include "window_renderer.hpp"

RendererWindow::RendererWindow() :
        window(NULL), renderer(NULL), canvas(NULL)
{
  
    window = SDL_CreateWindow(
        "Mead", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        0
    );
    if (window == NULL)
        std::cout << "SDL could not create  window!\n";

    renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED
    );

    if (renderer == NULL)
        std::cout << "SDL could not create renderer!\n";

    canvas = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );
}

SDL_Renderer* RendererWindow::GetRenderer() {
    return renderer;
}

SDL_Texture * RendererWindow::GetCanvas() {
  return canvas;
}

void RendererWindow::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;

    SDL_Quit();
}
