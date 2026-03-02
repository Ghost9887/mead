#include "ui_manager.hpp"

void draw_ui(const std::vector<Button> &buttons, SDL_Renderer *renderer) {
    for (Button btn : buttons) {
        btn.draw_button(renderer);
    }
}
