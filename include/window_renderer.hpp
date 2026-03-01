#ifndef WINDOW_RENDERER_HPP
#define WINDOW_RENDERER_HPP

#include "common.hpp"

class RendererWindow {
public: 
    RendererWindow();
    SDL_Renderer* GetRenderer();
    SDL_Texture * GetCanvas();
    void close();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *canvas;
};

#endif
