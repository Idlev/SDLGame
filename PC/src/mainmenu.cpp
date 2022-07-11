#include "mainmenu.h"

mainmenu::mainmenu(SDL_Texture *menu_tex, SDL_Texture *bg_tex, optionsmenu *options_m, scoremenu *score_m) : menu(menu_tex, bg_tex)
{
    rect_new_game.x = BLANK_X+30;
    rect_new_game.y = BLANK_Y+16;
    rect_new_game.w = 62;
    rect_new_game.h = 16;

    rect_options.x = BLANK_X+30;
    rect_options.y = BLANK_Y+37;
    rect_options.w = 62;
    rect_options.h = 16;

    rect_highscore.x = BLANK_X+30;
    rect_highscore.y = BLANK_Y+58;
    rect_highscore.w = 62;
    rect_highscore.h = 16;

    rect_exitgame.x = BLANK_X+30;
    rect_exitgame.y = BLANK_Y+73;
    rect_exitgame.w = 62;
    rect_exitgame.h = 16;

    options = options_m;
    score = score_m;

}

mainmenu::~mainmenu()
{
    //dtor
}


int mainmenu::action(std::stack<menu*> &stack_menu, int x, int y){

    int ans = 1;

    std::cout << "MAIN MENU ACTION" << std::endl;

    //CHECK IF MOUSE COORDINARES INSIDE MENU BOXES

    if( check_cursor(x,y,rect_new_game) ){

        std::cout << "NEW GAME" << std::endl;
        pop_menu(stack_menu);

    }else if( check_cursor(x,y, rect_options) ){

        std::cout << "OPTIONS" << std::endl;
        push_menu(stack_menu, options);

    }else if( check_cursor(x,y, rect_highscore)){

        std::cout << "HIGHSCORE" << std::endl;
        push_menu(stack_menu, score);

    }else if( check_cursor(x,y, rect_exitgame)){

        std::cout << "EXIT GAME" << std::endl;
        ans = 0;
        pop_menu(stack_menu);
    }

    return ans;
}
