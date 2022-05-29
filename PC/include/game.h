#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "player.h"
#include "apple.h"
#include "music.h"

class game
{
    public:
        game();
        ~game();

        void start();

    private:

    //MAIN LOOP
    bool is_running;

    //BUTTONS PRESSES
    bool key_left;
    bool key_right;

    //SCREEN
    SDL_Window *window;
    SDL_Renderer *renderer;
    static const int SCREEN_WIDTH = 256;
    static const int SCREEN_HEIGHT = 144;

    //FPS
    static const int FRAMES_PER_SECOND = 30;

    //BACKGROUND
    SDL_Surface *background_image;
    SDL_Texture *background_texture;
    SDL_Rect background_rect;

    //FUNCTIONS
    SDL_Surface *load_image(const char* filename);
    void handle_events();
    void show_background();
    void regulate_fps(Uint32 start);

    //GAME
    void game_logic();
    bool check_collision(SDL_Rect *rect1,SDL_Rect *rect2);

    //PLAYER
    player *player1;
    SDL_Surface *player_image;
    SDL_Texture *player_texture;

    //MUSIC
    music *music1;

    //APPLES
    std::vector<apple*> apple_vec;
    SDL_Surface *apple_image;
    SDL_Texture *apple_texture;
    void spawn_apple();
};

#endif // GAME_H

