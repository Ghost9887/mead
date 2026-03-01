#include "window_renderer.hpp"

RendererWindow::RendererWindow() :
        window(NULL), renderer(NULL)
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
}

SDL_Renderer* RendererWindow::GetRenderer() {
    return renderer;
}

void RendererWindow::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;

    SDL_Quit();
}
