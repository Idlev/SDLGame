#include "player.h"

player::player(SDL_Texture *player,SDL_Texture *extra)
{
    player_texture = player;
    extra_texture = extra;

    //STARTING POSITIONS
    x_pos = 60;
    y_pos = 120;

    //SPEED
    x_vel = 3;

    //0,1 LEFT,RIGHT
    face_dir = 1;

    //animation frame
    frame = 0;

    //Number of life points
    lives_count = 1;
    max_lives = 2;

    //PLAYER DIMENSIONS
    player_height = 20;
    player_width = 17;

    player_rect.x = x_pos;
    player_rect.y = y_pos;
    player_rect.w = player_width;
    player_rect.h = player_height;

    extra_size = 8;

    extra_rect1.x = 256-48-9;
    extra_rect1.y = 0;
    extra_rect1.w = extra_size;
    extra_rect1.h = extra_size;

    extra_rect2.x = 256-48-9-9;
    extra_rect2.y = 0;
    extra_rect2.w = extra_size;
    extra_rect2.h = extra_size;

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
    SDL_DestroyTexture(extra_texture);
}

//DRAW PLAYER
void player::show_player(SDL_Renderer *renderer){

    frame = 0;

    if(face_dir == 0) //LEFT
        SDL_RenderCopy(renderer, player_texture, &clips[5], &player_rect);
    else if(face_dir == 1) //RIGHT
        SDL_RenderCopy(renderer, player_texture, &clips[0], &player_rect);
}

void player::show_lives(SDL_Renderer *renderer){

    if(lives_count == 1){
        SDL_RenderCopy(renderer,extra_texture, NULL, &extra_rect1);
    }else if(lives_count == 2){
        SDL_RenderCopy(renderer,extra_texture, NULL, &extra_rect1);
        SDL_RenderCopy(renderer,extra_texture, NULL, &extra_rect2);
    }

}

void player::lose_life(){

    lives_count -= 1;;
}

void player::gain_life(){
    if(lives_count < max_lives){
        std::cout << "not max lives" << std::endl;
        lives_count += 1;
    }
}

int player::get_lives(){

    return lives_count;
}

void player::set_lives(int lives){

    lives_count = lives;
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

//MOVE, ANIMATION OF PLAYER, LEFT
void player::move_player_left(SDL_Renderer *renderer){
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

    frame++;
    if(frame >= 16)
        frame = 0;
}

//MOVE, ANIMATION PLAYER RIGHT
void player::move_player_right(SDL_Renderer *renderer){
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

    frame++;
    if(frame >= 16)
        frame = 0;
}

