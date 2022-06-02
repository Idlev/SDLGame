#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <stack>

#include "SDL2/SDL.h"
#include "menu.h"


class mainmenu : public menu
{
    public:
        mainmenu(SDL_Texture *menu_tex, SDL_Texture *bg_tex);
        ~mainmenu();

        void action(std::stack<menu*> &stack_menu, int x, int y);

    private:

        SDL_Rect rect_new_game;

};

#endif // MAINMENU_H
