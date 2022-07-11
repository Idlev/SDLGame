#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

class music
{
    public:
        music();
        ~music();

        void play_music();
        void play_effect();

        void lower_music();
        void lower_effect();
        void raise_music();
        void raise_effect();

        int get_music_vol();
        int get_effect_vol();

        int level_music;
        int level_effect;
        float interval;

    private:

        Mix_Music *game_music;
        Mix_Chunk *effect_apple;
};

#endif // MUSIC_H
