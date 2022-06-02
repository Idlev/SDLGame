#include "mainmenu.h"

mainmenu::mainmenu(SDL_Texture *menu_tex, SDL_Texture *bg_tex) : menu(menu_tex, bg_tex)
{

    rect_new_game.x = 68+30;
    rect_new_game.y = 12+16;
    rect_new_game.w = 62;
    rect_new_game.h = 16;

}

mainmenu::~mainmenu()
{
    //dtor
}

void mainmenu::action(std::stack<menu*> &stack_menu, int x, int y){

    std::cout << "MAIN MENU ACTION" << std::endl;

    if( (x >= rect_new_game.x and x <= rect_new_game.x + rect_new_game.w) &&
        (y >= rect_new_game.y and y <= rect_new_game.y + rect_new_game.h) ){

        std::cout << "MAIN MENU ACTION: NEW GAME" << std::endl;
        stack_menu.pop();

    }
}
