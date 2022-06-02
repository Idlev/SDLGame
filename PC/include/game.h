#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "player.h"
#include "apple.h"
#include "music.h"
#include "menu.h"
#include "mainmenu.h"
#include "optionsmenu.h"

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

    //MOUSE COORDINATES
    int mouse_x;
    int mouse_y;
    bool mouse_click;

    //SCALE
    int scale_current;

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

    //MENU SYSTEM

    SDL_Surface *title_bg_image;
    SDL_Texture *title_bg_texture;
    SDL_Surface *menu_image;
    SDL_Texture *menu_texture;
    SDL_Surface *options_image;
    SDL_Texture *options_texture;
    SDL_Rect menu_rect;
    void title_menu(Uint32 start);

    optionsmenu *optionsmenu1;
    mainmenu *mainmenu1;
    std::stack<menu*> menu_stack;
    void menu_system(Uint32 start);

    //FUNCTIONS
    SDL_Surface *load_image(const char* filename);
    void handle_events();
    void show_background();
    void regulate_fps(Uint32 start);

    //GAME
    int apple_counter;
    int counter_limit;

    void reset_game();
    void game_logic();
    bool check_collision(SDL_Rect *rect1,SDL_Rect *rect2);

    //PLAYER
    player *player1;
    SDL_Surface *player_image;
    SDL_Texture *player_texture;
    SDL_Surface *lives_image;
    SDL_Texture *lives_texture;

    //MUSIC
    music *music1;
    SDL_Surface *volume_image;
    SDL_Texture *volume_texture;

    //APPLES
    std::vector<apple*> apple_vec;
    SDL_Surface *apple_image;
    SDL_Surface *apple_sp_image;
    SDL_Texture *apple_texture;
    SDL_Texture *apple_sp_texture;

    void spawn_apple();
    void spawn_special();
};

#endif // GAME_H

