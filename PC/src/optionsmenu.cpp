#include "optionsmenu.h"

optionsmenu::optionsmenu(SDL_Texture *menu_tex, SDL_Texture *bg_tex, SDL_Texture *vol_tex, music *mus) : menu(menu_tex, bg_tex)
{
    rect_effect_plus.x = BLANK_X+91;
    rect_effect_plus.y = BLANK_Y+74;
    rect_effect_plus.w = 10;
    rect_effect_plus.h = 11;

    rect_effect_minus.x = BLANK_X+20;
    rect_effect_minus.y = BLANK_Y+74;
    rect_effect_minus.w = 10;
    rect_effect_minus.h = 11;

    rect_music_plus.x = BLANK_X+91;
    rect_music_plus.y = BLANK_Y+49;
    rect_music_plus.w = 10;
    rect_music_plus.h = 11;

    rect_music_minus.x = BLANK_X+20;
    rect_music_minus.y = BLANK_Y+49;
    rect_music_minus.w = 10;
    rect_music_minus.h = 11;

    volume_texture = vol_tex;
    music1 = mus;
}

optionsmenu::~optionsmenu()
{
    //dtor
}

void optionsmenu::show_menu(SDL_Renderer *renderer){


}

void optionsmenu::action(std::stack<menu*> &stack_menu, int x, int y){

    std::cout << "OPTIONSMENU ACTION:" << std::endl;

    //CHECK IF MOUSE COORDINARES INSIDE MENU BOXES

    if( check_cursor(x,y,rect_return) ){

        pop_menu(stack_menu);

    }


}
