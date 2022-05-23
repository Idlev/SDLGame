#include "apple.h"

apple::apple(SDL_Texture *texture, float x_p, float y_p, int vel)
{
    apple_texture = texture;

    x_pos = x_p;
    y_pos = y_p;

    //apple image w,h
    apple_size = 10;

    //frame
    frame = 0;

    apple_rect.x = x_pos;
    apple_rect.y = y_pos;
    apple_rect.w = apple_size;
    apple_rect.h = apple_size;

    for(int i=0 ; i<2; i++){
        clips[i].x = i*apple_size;
        clips[i].y = 0;
        clips[i].w = apple_size;
        clips[i].h = apple_size;
    }

    y_vel = vel;
}

apple::~apple()
{
    SDL_DestroyTexture(apple_texture);
}

SDL_Rect *apple::get_rect(){

    return &apple_rect;
}

//Num 0 for apple, 1 for empty
//SPAWN APPLE BLINKING
void apple::show_apple(SDL_Renderer *renderer){

    if(frame >= 0 and frame < 15)
        SDL_RenderCopy(renderer, apple_texture, &clips[0], &apple_rect);
    else if(frame >= 15 and frame < 30)
        SDL_RenderCopy(renderer, apple_texture, &clips[1], &apple_rect);
    else if(frame >= 30 and frame < 45)
        SDL_RenderCopy(renderer, apple_texture, &clips[0], &apple_rect);
    else if(frame >= 45 and frame < 60)
        SDL_RenderCopy(renderer, apple_texture, &clips[1], &apple_rect);
    else if(frame >= 60 and frame < 75)
        SDL_RenderCopy(renderer, apple_texture, &clips[0], &apple_rect);
    else if(frame >= 75 and frame < 90)
        SDL_RenderCopy(renderer, apple_texture, &clips[1], &apple_rect);
    else if(frame >= 90 and frame < 105)
        SDL_RenderCopy(renderer, apple_texture, &clips[0], &apple_rect);
    else
        SDL_RenderCopy(renderer, apple_texture, &clips[0], &apple_rect);

    frame++;
}

//AFTER SPWAN FALLS DOWN
void apple::move_apple(){

    if(frame < 105){
        //Do Nothing
    }
    else{
        y_pos += y_vel;
        apple_rect.y = y_pos;
    }
}

