#ifndef SCOREMENU_H
#define SCOREMENU_H

#include <iostream>

#include "SDL2/SDL.h"
#include "menu.h"

class scoremenu : public menu
{
    public:
        scoremenu(SDL_Texture *menu_tex, SDL_Texture *bg_tex);
        ~scoremenu();

        void show_menu(SDL_Renderer *renderer);
        int action(std::stack<menu*> &stack_menu, int x, int y);

    private:



};

#endif // SCOREMENU_H
