#include "engine.hpp"

void draw_circle(SDL_Renderer *renderer, int center_x, int center_y, int radius) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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

    SDL_Renderer *renderer = window->get_renderer();
    SDL_Texture *canvas = window->get_canvas();
    SDL_SetRenderTarget(renderer, canvas);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    SDL_Event event;

    std::vector<Button> buttons;
    Button test(50, 100, 100, 50, "Test");
    buttons.push_back(test);

    SDL_SetRenderTarget(renderer, canvas);
    draw_ui(buttons, renderer);

    bool running = true;
    while (running) {
        SDL_SetRenderTarget(renderer, canvas);

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
                            draw_circle(renderer, x, y, brush.size);
                            break;
                        case Rectangle:
                            break;
                        default:
                            break;
                    }
                }
            }
            
        }

        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, canvas, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}
