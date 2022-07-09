#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include <iostream>

#include "SDL2/SDL.h"
#include "music.h"
#include "menu.h"

class optionsmenu : public menu
{
    public:
        optionsmenu(SDL_Texture *menu_tex, SDL_Texture *bg_tex, SDL_Texture *vol_tex, music *mus);
        ~optionsmenu();

        void show_menu(SDL_Renderer *renderer);
        int action(std::stack<menu*> &stack_menu, int x, int y);

    private:

        SDL_Rect rect_effect_plus;
        SDL_Rect rect_effect_minus;
        SDL_Rect rect_music_plus;
        SDL_Rect rect_music_minus;

        SDL_Texture *volume_texture;
        music *music1;
};

#endif // OPTIONSMENU_H
