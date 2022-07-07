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
        void push_menu(std::stack<menu*> &stack_menu, menu* m);
        void pop_menu(std::stack<menu*> &stack_menu);
        bool check_cursor(int x, int y, SDL_Rect rect);

        const int BLANK_X = 68;
        const int BLANK_Y = 12;

        SDL_Rect rect_return;

    protected:

        SDL_Texture *menu_texture;
        SDL_Texture *bg_texture;

        SDL_Rect menu_rect;
        SDL_Rect bg_rect;
};

#endif // MENU_H
