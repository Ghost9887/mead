#include "window_renderer.hpp"

RendererWindow::RendererWindow() :
        window(nullptr), renderer(nullptr), canvas(nullptr), font(nullptr)
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
    
    if (TTF_Init() == -1) {
        std::cout << "TTF_Init error: " << TTF_GetError() << std::endl;
    }

    font = TTF_OpenFont("../fonts/open_sans.ttf", 24);

    if (!font) {
        std::cout << "SDL could not find font!\n";
    }
}

SDL_Renderer *RendererWindow::get_renderer() {
    return renderer;
}

SDL_Texture *RendererWindow::get_canvas() {
  return canvas;
}

TTF_Font *RendererWindow::get_font() {
    return font;
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
