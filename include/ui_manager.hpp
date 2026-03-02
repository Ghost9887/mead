#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP

#include "common.hpp"
#include "button.hpp"

void draw_ui(const std::vector<Button> &buttons, SDL_Renderer *renderer);

#endif
