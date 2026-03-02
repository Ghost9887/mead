#include "button.hpp"

Button::Button(int x, int y, int width, int height, std::string text, TTF_Font *font) :
    state(false), text(text), rect(), font(font) 
{
    rect = { x, y, width, height };
}


void Button::press_button() {
    state = !state;
}

void Button::draw_button(SDL_Renderer *renderer) {
    SDL_RenderFillRect(renderer, &rect);

    SDL_Color textColor = { 0, 0, 0, 255 };
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &rect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    textTexture = nullptr;
    textSurface = nullptr;
}
