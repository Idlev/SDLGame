//SDL Game development for android

#include "SDL.h"
#include "SDL_image.h"

#include "stdio.h"
#include "string"
#include "string.h"
#include "vector"
#include "cstdlib"
#include "stdlib.h"

#include "player.h"
#include "apple.h"

//fps
const int FRAMES_PER_SECOND = 30;
int frame_counter = 0;
//For texture/window scaling
int scale = 0;
int screen_offset = 0;

//directions for player
bool left = false;
bool right = false;

//Main loop flag
bool is_running = true;

player *player1 = NULL;
std::vector<apple*> apple_vec;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Surface *bg_image = NULL;
SDL_Texture *bg_texture = NULL;

SDL_Surface *player_image = NULL;
SDL_Texture *player_texture = NULL;

SDL_Surface *apple_image = NULL;
SDL_Texture *apple_texture = NULL;

//Screen dimension
SDL_Rect screenRect = {0,0,256,144};

SDL_Surface *load_image(std::string path){

    SDL_Surface *tmp = IMG_Load(path.c_str());

    if(tmp == NULL){
        SDL_Log("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    return tmp;
}

SDL_Texture *create_texture(SDL_Surface *img){
    SDL_Texture *tmp = SDL_CreateTextureFromSurface(renderer, img);
    
    if(tmp == NULL){
        SDL_Log("Unable to create texture! SDL Error: %s\n", SDL_GetError());
    }
    
    return tmp;
}

bool init(){

	bool res = true;

	//Init SDL
	if( SDL_Init(SDL_INIT_EVERYTHING) < 0){
        SDL_Log("SDL Init error! : SDL Error: %s\n", SDL_GetError());
        res = false;
	}else{

        //Get device display mode
        SDL_DisplayMode dispMode;
        if(SDL_GetCurrentDisplayMode(0,&dispMode) == 0){
            //screenRect.w = dispMode.w;
            //screenRect.h = dispMode.h;
        }

        //Calculate scale depending on phone resolution
        //float scale = dispMode.w / 256;

        //Create window
        window = SDL_CreateWindow("SDL_Test", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,screenRect.w,screenRect.h,SDL_WINDOW_FULLSCREEN);
        if(window == NULL){
            SDL_Log("Window not created! SDL Error: %s\n", SDL_GetError());
            res = false;

        }else{
            //Create renderer
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer == NULL){
                SDL_Log("Renderer not created! SDL Error: %s\n", SDL_GetError());
                res = false;
            }
        }

        SDL_SetWindowSize(window,dispMode.w,dispMode.h);
        SDL_RenderSetScale(renderer,5,5);

    }

    return res;
}

bool loadMedia(){
    
    bool res = true;

    bg_image = load_image("sdltest/bg4.png");
    if(bg_image == NULL){
        SDL_Log("Failed to load bg image \n");
        res = false;
    }

    player_image = load_image("sdltest/playerFrames.png");
    if(player_image == NULL){
        SDL_Log("Failed to load player image \n");
        res = false;
    }

    apple_image = load_image("sdltest/apple6.png");
    if(apple_image == NULL){
        SDL_Log("Failed to load apple image \n");
        res = false;
    }

    bg_texture = create_texture(bg_image);
    if(bg_texture == NULL){
        SDL_Log("Failed to create bg texture \n");
        res = false;
    }

    player_texture = create_texture(player_image);
    if(player_texture == NULL){
        SDL_Log("Failed to create player texture");
        res = false;
    }

    apple_texture = create_texture(apple_image);
    if(apple_texture == NULL){
        SDL_Log("Failed to create apple texture");
        res = false;
    }

    return res;
}

bool check_collision(SDL_Rect *rect1, SDL_Rect *rect2){

    if(rect1->y >= rect2->y+rect2->h)
        return 0;
    if(rect1->x >= rect2->x+rect2->w)
        return 0;
    if(rect1->y + rect1->h <= rect2->y)
        return 0;
    if(rect1->x + rect1->w <= rect2->x)
        return 0;

    //IF NONE OF ABOVE CONDITIONS FULLFIL RECTANGLES OVERLAP -> COLLISION
    return 1;
}

void game_logic(){

    //CHECK PLAYER BOUNDS
    if(player1->get_rect()->x < 48)
        player1->set_x_pos(48);
    else if(player1->get_rect()->x > 160+48-player1->get_rect()->w)
        player1->set_x_pos(160+48-player1->get_rect()->w);

    //MOVE APPLEs
    if(apple_vec.size() > 0){
        for(unsigned int i=0; i<apple_vec.size(); i++){
            apple_vec[i]->move_apple();
            apple_vec[i]->show_apple(renderer);
        }
    }

    //Move PLayer
    if(left == true){
        player1->move_player_left(renderer,frame_counter);
        frame_counter++;
    }else if(right == true){
        player1->move_player_right(renderer,frame_counter);
        frame_counter++;
    }else{
        player1->show_player(renderer);
    }

    if(frame_counter >= 16)
        frame_counter = 0;

    //CHECK APPLE PLAYER COLLISION
    if(apple_vec.size() > 0){
        for(unsigned int i=0; i<apple_vec.size(); i++){
            if(check_collision(player1->get_rect(),apple_vec[i]->get_rect())){
                apple_vec.erase(apple_vec.begin()+i);
            }
        }
    }

}

void spawn_apple(){
    apple_vec.push_back(new apple(apple_texture,std::rand()%150+50,std::rand()%10+5,3));
}

void regulate_fps(Uint32 start){
    if(1000 / FRAMES_PER_SECOND > (SDL_GetTicks() - start))
        SDL_Delay(1000 / FRAMES_PER_SECOND - (SDL_GetTicks() -start));
}

void handle_events(){

    //Event handler
    SDL_Event event;
    SDL_Point touch_location = {screenRect.w/2,screenRect.h/2};

    while (SDL_PollEvent(&event)) {

        switch (event.type) {
            case SDL_QUIT:
                is_running = false;
                break;

            case SDL_FINGERDOWN:
                if(event.tfinger.x < 0.5)
                    left = true;
                else
                    right = true;

                break;

            case SDL_FINGERUP:
                left = false;
                right = false;
                break;
        }
    }
}

void close_all(){
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(bg_image);
    SDL_DestroyTexture(bg_texture);
    
    SDL_Quit();
}

int main(int argc, char* args[]){

    if(!init()){
        SDL_Log("Failed init \n");
    }else {
        if (!loadMedia()) {
            SDL_Log("Failed to load media \n");
        } else {

            player1 = new player(player_texture);

            //for fps
            Uint32 start = 0;
            int frame = 0;

            //Main loop
            while (is_running) {

                start = SDL_GetTicks();

                handle_events();

                //show background
                SDL_RenderCopy(renderer, bg_texture, NULL, &screenRect);

                game_logic();

                frame++;
                if(frame == 150){
                    spawn_apple();
                    frame = 0;
                }


                SDL_RenderPresent(renderer);
                regulate_fps(start);
            }
        }
    }
    close_all();
    return 0;
}