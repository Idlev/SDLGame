#include "menu.h"

menu::menu(SDL_Texture *menu_tex,SDL_Texture *bg_tex)
{
    menu_texture = menu_tex;
    bg_texture = bg_tex;

    menu_rect.x = 68;
    menu_rect.y = 12;
    menu_rect.w = 120;
    menu_rect.h = 120;

    bg_rect.x = 0;
    bg_rect.y = 0;
    bg_rect.w = 256;
    bg_rect.h = 144;
}

menu::~menu()
{
    SDL_DestroyTexture(menu_texture);
}

void menu::show_menu(SDL_Renderer *renderer){

    SDL_RenderCopy(renderer, bg_texture, NULL, &bg_rect);
    SDL_RenderCopy(renderer, menu_texture, NULL, &menu_rect);
}

void menu::action(std::stack<menu*> &stack_menu, int x, int y){

    std::cout << "actions here" << std::endl;
}
