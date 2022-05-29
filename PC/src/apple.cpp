#include "apple.h"

apple::apple(SDL_Texture *texture, float x_p, float y_p, int vel, bool sp)
{
    apple_texture = texture;

    x_pos = x_p;
    y_pos = y_p;

    //apple image w,h
    apple_size = 10;

    //animation frame
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
    is_special = sp;
}

apple::~apple()
{
    SDL_DestroyTexture(apple_texture);
}

SDL_Rect *apple::get_rect(){

    return &apple_rect;
}

bool apple::get_special(){
    return is_special;
}

//Num 0 for apple, 1 for empty
//SPAWN APPLE BLINKING
void apple::show_apple(SDL_Renderer *renderer){

    if(frame >= 0 and frame < 10)
        SDL_RenderCopy(renderer, apple_texture, &clips[0], &apple_rect);
    else if(frame >= 10 and frame < 20)
        SDL_RenderCopy(renderer, apple_texture, &clips[1], &apple_rect);
    else if(frame >= 20 and frame < 30)
        SDL_RenderCopy(renderer, apple_texture, &clips[0], &apple_rect);
    else if(frame >= 30 and frame < 40)
        SDL_RenderCopy(renderer, apple_texture, &clips[1], &apple_rect);
    else if(frame >= 40 and frame < 50)
        SDL_RenderCopy(renderer, apple_texture, &clips[0], &apple_rect);
    else if(frame >= 50 and frame < 60)
        SDL_RenderCopy(renderer, apple_texture, &clips[1], &apple_rect);
    else if(frame >= 60 and frame < 70)
        SDL_RenderCopy(renderer, apple_texture, &clips[0], &apple_rect);
    else if(frame >= 70 and frame < 80)
        SDL_RenderCopy(renderer, apple_texture, &clips[1], &apple_rect);
    else if(frame >= 80 and frame < 85)
        SDL_RenderCopy(renderer, apple_texture, &clips[0], &apple_rect);
    else if(frame >= 85 and frame < 90)
        SDL_RenderCopy(renderer, apple_texture, &clips[1], &apple_rect);
    else if(frame >= 90 and frame < 95)
        SDL_RenderCopy(renderer, apple_texture, &clips[0], &apple_rect);
    else if(frame >= 95 and frame < 100)
        SDL_RenderCopy(renderer, apple_texture, &clips[1], &apple_rect);
    else if(frame >= 100 and frame < 105)
        SDL_RenderCopy(renderer, apple_texture, &clips[0], &apple_rect);
    else if(frame >= 105 and frame < 110)
        SDL_RenderCopy(renderer, apple_texture, &clips[0], &apple_rect);
    else
        SDL_RenderCopy(renderer, apple_texture, &clips[0], &apple_rect);

    frame++;
}

//AFTER SPWAN FALLS DOWN
void apple::move_apple(){

    if(frame < 110){
        //Do Nothing
    }
    else{
        y_pos += y_vel;
        apple_rect.y = y_pos;
    }
}


