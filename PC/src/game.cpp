#include "game.h"

game::game()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Apples",
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    256,144,SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(window, -1, 0);

    background_rect.x = 0;
    background_rect.y = 0;
    background_rect.w = SCREEN_WIDTH;
    background_rect.h = SCREEN_HEIGHT;

    is_running = true;
    key_left = false;
    key_right = false;

    background_image = load_image("bg4.png");
    background_texture = SDL_CreateTextureFromSurface(renderer, background_image);
    player_image = load_image("PlayerFrames.png");
    player_texture = SDL_CreateTextureFromSurface(renderer, player_image);
    apple_image = load_image("apple6.png");
    apple_texture = SDL_CreateTextureFromSurface(renderer, apple_image);

    player1 = new player(player_texture);
    music1 = new music();
}

game::~game()
{
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(player_texture);
    SDL_DestroyTexture(apple_texture);
}

//IMAGE LOAD FUNCTION FOR PLAYER, BACKGROUND, APPLES
SDL_Surface *game::load_image(const char *filename){

    SDL_Surface *tmp = IMG_Load(filename);

    if(tmp == NULL)
        std::cout << "Error loading image" << std::endl;

    return tmp;
}

//FPS REGULATOR
void game::regulate_fps(Uint32 start){
    if(1000 / FRAMES_PER_SECOND > (SDL_GetTicks() - start))
        SDL_Delay(1000 / FRAMES_PER_SECOND - (SDL_GetTicks() -start));
}

//COLLISION CHECKING, BOUNDING BOX PRINCIPLE
bool game::check_collision(SDL_Rect *rect1, SDL_Rect *rect2){

    if(rect1->y >= rect2->y+rect2->h)
        return 0;
    if(rect1->x >= rect2->x+rect2->w)
        return 0;
    if(rect1->y + rect1->h <= rect2->y)
        return 0;
    if(rect1->x + rect1->w <= rect2->x)
        return 0;

    //IF WE GET HERE -> COLLISION
    return 1;
}


//KEYBOARD EVENTS, MOVE PLAYER, SCALE WINDOW
void game::handle_events(){

    SDL_Event event;

    while(SDL_PollEvent(&event)){

        switch(event.type){
            case SDL_QUIT:
                is_running = false;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){

                    case SDLK_LEFT:
                        std::cout << "moving left" << std::endl;
                        key_left = true;
                        key_right = false;
                        break;

                    case SDLK_RIGHT:
                        std::cout << "moving right" << std::endl;
                        key_right = true;
                        key_left = false;
                        break;

                    case SDLK_1:
                        SDL_SetWindowSize(window,256,144);
                        SDL_RenderSetScale(renderer,1,1);
                        break;

                    case SDLK_2:
                        SDL_SetWindowSize(window,256*2,144*2);
                        SDL_RenderSetScale(renderer,2,2);
                        break;

                    case SDLK_3:
                        SDL_SetWindowSize(window,256*3,144*3);
                        SDL_RenderSetScale(renderer,3,3);
                        break;

                    case SDLK_4:
                        SDL_SetWindowSize(window,256*4,144*4);
                        SDL_RenderSetScale(renderer,4,4);
                        break;

                    default:
                        NULL;
                }
            break;

            case SDL_KEYUP:
                switch(event.key.keysym.sym){

                case SDLK_LEFT:
                    std::cout << "stopped moving left" << std::endl;
                    key_left = false;
                    break;

                case SDLK_RIGHT:
                    std::cout << "stopped moving right" << std::endl;
                    key_right = false;
                    break;

                default:
                    NULL;
            }
            break;
        }
    }
}

//SPWAN APPLE
void game::spawn_apple(){

    apple_vec.push_back(new apple(apple_texture,rand()%145+50,rand()%35+5,3));
}

void game::game_logic(){

    //CHECK PLAYER BOUNDS
    if(player1->get_rect()->x < 48)
        player1->set_x_pos(48);
    else if(player1->get_rect()->x > 160+48-player1->get_rect()->w)
        player1->set_x_pos(160+48-player1->get_rect()->w);

    //MOVE APPLES
    if(apple_vec.size() > 0){
        for(unsigned int i=0; i<apple_vec.size(); i++){
            apple_vec[i]->move_apple();
            apple_vec[i]->show_apple(renderer);
        }
    }

    //MOVE PLAYER
    if(key_left == true){
        player1->move_player_left(renderer);
    }else if(key_right == true){
        player1->move_player_right(renderer);
    }else{
        player1->show_player(renderer);
    }

    //CHECK APPLE PLAYER COLLISION
    if(apple_vec.size() > 0){
        for(unsigned int i=0; i<apple_vec.size(); i++){
            if(check_collision(player1->get_rect(),apple_vec[i]->get_rect())){
                std::cout << "Caught an apple!" << std::endl;
                music1->play_effect();
                apple_vec.erase(apple_vec.begin()+i);
            }

            //CHECK LOSING CONDITION
            if( apple_vec[i]->get_rect()->y > player1->get_rect()->y+player1->get_rect()->h){
                std::cout << "Apple missed! Game over!" << std::endl;
                is_running = false;
            }
        }
    }
}

//DRAW BACKGROUND
void game::show_background(){

    //SDL_RenderCopy(renderer, background_texture, NULL, &background_rect);
    SDL_RenderCopy(renderer, background_texture, NULL, NULL);
}


//Main game
void game::start(){

    Uint32 start;
    srand(time(0));

    int apple_counter = 0;
    int counter_limit = 45;

    music1->play_music();

    //Main game loop
    while(is_running){

        start = SDL_GetTicks();

        handle_events();

        show_background();

        game_logic();

        apple_counter++;
        if(apple_counter == counter_limit){
            spawn_apple();
            apple_counter = 0;
            counter_limit = rand()%45+26; //spawn apple at 30-70 frames
        }

        SDL_RenderPresent(renderer);

        regulate_fps(start);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


