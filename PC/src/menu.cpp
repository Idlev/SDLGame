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

    rect_return.x = BLANK_X+91;
    rect_return.y = BLANK_Y+99;
    rect_return.w = 16;
    rect_return.h = 14;
}

menu::~menu()
{
    SDL_DestroyTexture(menu_texture);
}

void menu::show_menu(SDL_Renderer *renderer){

    SDL_RenderCopy(renderer, bg_texture, NULL, &bg_rect);
    SDL_RenderCopy(renderer, menu_texture, NULL, &menu_rect);

}

int menu::action(std::stack<menu*> &stack_menu, int x, int y){

    int ans = 1;

    std::cout << "actions here" << std::endl;

    return ans;
}

void menu::push_menu(std::stack<menu*> &stack_menu, menu* m){

    stack_menu.push(m);
}

void menu::pop_menu(std::stack<menu*> &stack_menu){

    stack_menu.pop();
}

bool menu::check_cursor(int x, int y, SDL_Rect rect){

    bool ans = false;

    if( ( x >= rect.x and x <= rect.x + rect.w) && (y >= rect.y and y <= rect.y + rect.h) )
        ans = true;

    return ans;
}
