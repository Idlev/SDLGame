#ifndef APPLE_H
#define APPLE_H

#include "SDL2/SDL.h"

class apple
{
    public:
        apple(SDL_Texture *texture, float x_p, float y_p, int vel, bool sp);
        ~apple();

        void show_apple(SDL_Renderer *renderer);
        void move_apple();
        float set_y_vel(float vel);
        SDL_Rect *get_rect();
        SDL_Rect *get_coll_rect();
        bool get_special();

    private:

        SDL_Texture *apple_texture;
        SDL_Rect apple_rect;
        SDL_Rect coll_rect;
        SDL_Rect clips[2];

        float x_pos;
        float y_pos;

        float y_vel;

        int apple_size;
        int frame;
        bool is_special;
};

#endif // APPLE_H
