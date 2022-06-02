#include "mainmenu.h"

mainmenu::mainmenu(SDL_Texture *menu_tex, SDL_Texture *bg_tex, optionsmenu *options_m) : menu(menu_tex, bg_tex)
{
    rect_new_game.x = BLANK_X+30;
    rect_new_game.y = BLANK_Y+16;
    rect_new_game.w = 62;
    rect_new_game.h = 16;

    rect_options.x = BLANK_X+30;
    rect_options.y = BLANK_Y+37;
    rect_options.w = 62;
    rect_options.h = 16;

    options = options_m;
}

mainmenu::~mainmenu()
{
    //dtor
}


void mainmenu::action(std::stack<menu*> &stack_menu, int x, int y){

    std::cout << "MAIN MENU ACTION" << std::endl;

    //CHECK IF MOUSE COORDINARES INSIDE MENU BOXES

    if( check_cursor(x,y,rect_new_game) ){

        std::cout << "NEW GAME" << std::endl;
        pop_menu(stack_menu);

    }else if( check_cursor(x,y, rect_options) ){

        std::cout << "OPTIONS" << std::endl;
        push_menu(stack_menu, options);

    }


}

