#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cmath>

#include "SDL.h"

class player
{
    public:
        player(SDL_Texture *texture);
        ~player();

        void show_player(SDL_Renderer *renderer);
        void move_player_right(SDL_Renderer *renderer, int &frame);
        void move_player_left(SDL_Renderer *renderer, int &frame);
        SDL_Rect *get_rect();

        float get_x_vel();
        void set_x_vel(float vel);
        void set_x_pos(float pos);

    private:

        SDL_Texture *player_texture;
        SDL_Rect player_rect;
        SDL_Rect clips[10];

        float x_pos;
        float y_pos;
        float x_vel;

        int player_height;
        int player_width;
        int face_dir;
};

#endif // PLAYER_H
