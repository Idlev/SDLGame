#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "SDL2/SDL.h"

class player
{
    public:
        player(SDL_Texture *texture_plr,SDL_Texture *texture_extra);
        ~player();

        void show_player(SDL_Renderer *renderer);
        void move_player_right(SDL_Renderer *renderer);
        void move_player_left(SDL_Renderer *renderer);
        SDL_Rect *get_rect();

        float get_x_vel();
        void set_x_vel(float vel);
        void set_x_pos(float pos);

        int get_lives();
        void set_lives(int lives);
        void lose_life();
        void gain_life();
        void show_lives(SDL_Renderer *renderer);

    private:

        SDL_Texture *player_texture;
        SDL_Rect player_rect;
        SDL_Rect clips[10];

        int extra_size;
        SDL_Texture *extra_texture;
        SDL_Rect extra_rect1;
        SDL_Rect extra_rect2;

        float x_pos;
        float y_pos;
        float x_vel;

        int player_height;
        int player_width;
        int face_dir;
        int frame;

        int lives_count;
        int max_lives;
};

#endif // PLAYER_H

