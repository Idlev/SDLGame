#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <stack>

#include "SDL2/SDL.h"
#include "menu.h"
#include "optionsmenu.h"
#include "scoremenu.h"

class mainmenu : public menu
{
    public:
        mainmenu(SDL_Texture *menu_tex, SDL_Texture *bg_tex, optionsmenu *options_m, scoremenu *score_m);
        ~mainmenu();

        int action(std::stack<menu*> &stack_menu, int x, int y);

    private:

        SDL_Rect rect_new_game;
        SDL_Rect rect_options;
        SDL_Rect rect_highscore;
        SDL_Rect rect_exitgame;

        optionsmenu *options;
        scoremenu *score;
};

#endif // MAINMENU_H
