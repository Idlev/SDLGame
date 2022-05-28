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

    private:

        Mix_Music *game_music;
        Mix_Chunk *effect_apple;
};

#endif // MUSIC_H

