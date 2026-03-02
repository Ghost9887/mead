#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "common.hpp"

class Button {
public:
    Button(int x, int y, int width, int height, std::string text, TTF_Font *font);
    void press_button();
    void draw_button(SDL_Renderer *renderer);
private:
    bool state;
    SDL_Rect rect;
    TTF_Font *font;
    std::string text;
};

#endif
