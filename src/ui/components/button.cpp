#include "button.hpp"

Button::Button(int x, int y, int width, int height, std::string text) :
    state(false), text(text), rect() 
{
    rect = { x, y, width, height };
}


void Button::press_button() {
    state = !state;
}

void Button::draw_button(SDL_Renderer *renderer) {
    SDL_RenderFillRect(renderer, &rect);
}
