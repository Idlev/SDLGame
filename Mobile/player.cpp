#include "player.h"

player::player(SDL_Texture *texture, int x_offset, int y_offset)
{
    player_texture = texture;

    x_pos = 60+x_offset;
    y_pos = 120+y_offset;

    x_vel = 3;

    //0,1 LEFT,RIGHT
    face_dir = 1;

    player_height = 20;
    player_width = 17;

    player_rect.x = x_pos;
    player_rect.y = y_pos;
    player_rect.w = player_width;
    player_rect.h = player_height;

    //10 individual images
    for(int i=0; i<10; i++){
        clips[i].x = i*player_width;
        clips[i].y = 0;
        clips[i].w = player_width;
        clips[i].h = player_height;
    }
}

player::~player()
{
    SDL_DestroyTexture(player_texture);
}

void player::show_player(SDL_Renderer *renderer){

    if(face_dir == 0) //LEFT
        SDL_RenderCopy(renderer, player_texture, &clips[5], &player_rect);
    else if(face_dir == 1) //RIGHT
        SDL_RenderCopy(renderer, player_texture, &clips[0], &player_rect);
}

SDL_Rect *player::get_rect(){

    return &player_rect;
}

float player::get_x_vel(){

    return x_vel;
}

void player::set_x_vel(float vel){

    std::cout << "player vel set to: " << vel << std::endl;
    x_vel = vel;
}

void player::set_x_pos(float pos){
    x_pos = pos;
    player_rect.x = x_pos;
}

void player::move_player_left(SDL_Renderer *renderer, int &frame){
    face_dir = 0;
    x_pos -= x_vel;

    if(frame >= 0 and frame < 4)
        SDL_RenderCopy(renderer, player_texture, &clips[6], &player_rect);
    else if(frame >= 4 and frame < 8)
        SDL_RenderCopy(renderer, player_texture, &clips[7], &player_rect);
    else if(frame >= 8 and frame < 12)
        SDL_RenderCopy(renderer, player_texture, &clips[8], &player_rect);
    else if (frame >= 12 and frame < 16)
        SDL_RenderCopy(renderer, player_texture, &clips[9], &player_rect);

    player_rect.x = x_pos;
}

void player::move_player_right(SDL_Renderer *renderer, int &frame){
    face_dir = 1;
    x_pos += x_vel;

    if(frame >= 0 and frame < 4)
        SDL_RenderCopy(renderer, player_texture, &clips[1], &player_rect);
    else if(frame >= 4 and frame < 8)
        SDL_RenderCopy(renderer, player_texture, &clips[2], &player_rect);
    else if(frame >= 8 and frame < 12)
        SDL_RenderCopy(renderer, player_texture, &clips[3], &player_rect);
    else if (frame >= 12 and frame < 16)
        SDL_RenderCopy(renderer, player_texture, &clips[4], &player_rect);

    player_rect.x = x_pos;
}



