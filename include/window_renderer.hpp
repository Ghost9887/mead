#ifndef WINDOW_RENDERER_HPP
#define WINDOW_RENDERER_HPP

#include "common.hpp"

class RendererWindow {
public: 
    RendererWindow();
    ~RendererWindow();
    SDL_Renderer *get_renderer();
    SDL_Texture *get_canvas();
    void close();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *canvas;
};

#endif
