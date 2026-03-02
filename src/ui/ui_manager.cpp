#include "ui_manager.hpp"

void draw_ui(const std::vector<Button> &buttons, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 50, 100, 255, 255);
    for (Button btn : buttons) {
        btn.draw_button(renderer);
    }
}
