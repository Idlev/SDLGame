#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <stack>

#include "SDL2/SDL.h"

class menu
{
    public:
        menu(SDL_Texture *menu_tex, SDL_Texture *bg_tex);
        ~menu();

        void show_menu(SDL_Renderer *renderer);
        virtual void action(std::stack<menu*> &stack_menu,int x, int y);

    private:

        SDL_Texture *menu_texture;
        SDL_Texture *bg_texture;

        SDL_Rect menu_rect;
        SDL_Rect bg_rect;
};

#endif // MENU_H
