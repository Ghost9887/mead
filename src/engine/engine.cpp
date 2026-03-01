#include "engine.hpp"

void draw_circle(SDL_Renderer* renderer, int center_x, int center_y, int radius) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int x, y;
    for (int angle = 0; angle < 360; angle++) {
        double rad_angle = angle * M_PI / 180.0; 
        x = static_cast<int>(center_x + radius * cos(rad_angle));
        y = static_cast<int>(center_y + radius * sin(rad_angle));
        SDL_RenderDrawLine(renderer, center_x, center_y, x, y);
    }
}

void Engine::run(RendererWindow *window) {
    Brush brush(Default, Circle, 20);

    SDL_Renderer *renderer = window->GetRenderer();
    SDL_Texture *canvas = window->GetCanvas();
    SDL_Event event;

    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.motion.state & SDL_BUTTON_LMASK) {
                    int x = event.motion.x;
                    int y = event.motion.y;
                    switch (brush.shape) {
                        case Circle: 
                            SDL_SetRenderTarget(renderer, canvas);
                            draw_circle(renderer, x, y, brush.size);
                            SDL_SetRenderTarget(renderer, NULL);
                            break;
                        case Rectangle:
                            break;
                        default:
                            break;
                    }
                }
            }
            
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, canvas, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}
