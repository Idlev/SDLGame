#include "scoremenu.h"

scoremenu::scoremenu(SDL_Texture *menu_tex, SDL_Texture *bg_tex) : menu(menu_tex, bg_tex)
{
    //ctor
}

scoremenu::~scoremenu()
{
    //dtor
}

void scoremenu::show_menu(SDL_Renderer *renderer){

    SDL_RenderCopy(renderer, bg_texture, NULL, &bg_rect);
    SDL_RenderCopy(renderer, menu_texture, NULL, &menu_rect);

}

int scoremenu::action(std::stack<menu*> &stack_menu, int x, int y){

    int ans = 1;

    std::cout << "SCOREMENY ACTION: " << std::endl;

    if( check_cursor(x,y,rect_return) ){
        pop_menu(stack_menu);
    }

    return ans;
}
