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

    apple_counter = 0;
    counter_limit = 45;

    //scale
    scale_current = 1;

    //player movement
    key_left = false;
    key_right = false;
    mouse_click = false;

    //mouse coordinates
    mouse_x = 0;
    mouse_y = 0;

    background_image = load_image("bg4.png");
    background_texture = SDL_CreateTextureFromSurface(renderer, background_image);
    title_bg_image = load_image("title_bg.png");
    title_bg_texture = SDL_CreateTextureFromSurface(renderer, title_bg_image);
    menu_image = load_image("menu2.png");
    menu_texture = SDL_CreateTextureFromSurface(renderer,menu_image);
    options_image = load_image("options.png");
    options_texture = SDL_CreateTextureFromSurface(renderer,options_image);

    player_image = load_image("PlayerFrames.png");
    player_texture = SDL_CreateTextureFromSurface(renderer, player_image);
    lives_image = load_image("extralife.png");
    lives_texture = SDL_CreateTextureFromSurface(renderer, lives_image);

    apple_image = load_image("apple6.png");
    apple_texture = SDL_CreateTextureFromSurface(renderer, apple_image);
    apple_sp_image = load_image("applesp.png");
    apple_sp_texture = SDL_CreateTextureFromSurface(renderer,apple_sp_image);

    volume_image = load_image("volume.png");
    volume_texture = SDL_CreateTextureFromSurface(renderer,volume_image);

    player1 = new player(player_texture,lives_texture);
    music1 = new music();
    optionsmenu1 = new optionsmenu(options_texture,title_bg_texture,volume_texture,music1);
    mainmenu1 = new mainmenu(menu_texture,title_bg_texture,optionsmenu1);
}

game::~game()
{
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(player_texture);
    SDL_DestroyTexture(apple_texture);
    SDL_DestroyTexture(apple_sp_texture);
    SDL_DestroyTexture(title_bg_texture);
    SDL_DestroyTexture(menu_texture);
    SDL_DestroyTexture(volume_texture);

    SDL_FreeSurface(player_image);
    SDL_FreeSurface(apple_image);
    SDL_FreeSurface(apple_sp_image);
    SDL_FreeSurface(title_bg_image);
    SDL_FreeSurface(menu_image);
    SDL_FreeSurface(volume_image);
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
                SDL_Quit();
                is_running = false;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){

                    case SDLK_LEFT:
                        //std::cout << "moving left" << std::endl;
                        key_left = true;
                        key_right = false;
                        break;

                    case SDLK_RIGHT:
                        //std::cout << "moving right" << std::endl;
                        key_right = true;
                        key_left = false;
                        break;

                    case SDLK_1:
                        SDL_SetWindowSize(window,256,144);
                        SDL_RenderSetScale(renderer,1,1);
                        scale_current = 1;
                        break;

                    case SDLK_2:
                        SDL_SetWindowSize(window,256*2,144*2);
                        SDL_RenderSetScale(renderer,2,2);
                        scale_current = 2;
                        break;

                    case SDLK_3:
                        SDL_SetWindowSize(window,256*3,144*3);
                        SDL_RenderSetScale(renderer,3,3);
                        scale_current = 3;
                        break;

                    case SDLK_4:
                        SDL_SetWindowSize(window,256*4,144*4);
                        SDL_RenderSetScale(renderer,4,4);
                        scale_current = 4;
                        break;

                    default:
                        NULL;
                }

                break;

            case SDL_KEYUP:
                switch(event.key.keysym.sym){

                case SDLK_LEFT:
                    //std::cout << "stopped moving left" << std::endl;
                    key_left = false;
                    break;

                case SDLK_RIGHT:
                    //std::cout << "stopped moving right" << std::endl;
                    key_right = false;
                    break;

                default:
                    NULL;
                }

                break;


            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button){

                    case SDL_BUTTON_LEFT:
                        if(!menu_stack.empty()){
                            mouse_click = true;
                            std::cout << "Mouse at x,y: " << mouse_x << "," << mouse_y << std::endl;
                        }
                        break;

                }
                break;

            case SDL_MOUSEMOTION:
                mouse_x = event.motion.x/scale_current;
                mouse_y = event.motion.y/scale_current;
                break;
        }
    }
}

//SPWAN APPLE
void game::spawn_apple(){

    apple_vec.push_back(new apple(apple_texture,rand()%145+50,rand()%35+5,3,false));
}

void game::spawn_special(){

    if(rand()%10 == 0)
        apple_vec.push_back(new apple(apple_sp_texture,rand()%145+50,rand()%35+5,1,true));
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

    //SHOW LIVES
    player1->show_lives(renderer);

    //CHECK APPLE PLAYER COLLISION
    if(apple_vec.size() > 0){
        for(unsigned int i=0; i<apple_vec.size(); i++){
            if(check_collision(player1->get_rect(),apple_vec[i]->get_rect())){
                std::cout << "Caught an apple!" << std::endl;

                if(apple_vec[i]->get_special()){
                    std::cout << "SPECIAL CAUGHT" << std::endl;
                    player1->gain_life();
                    std::cout << "Curr lives: " << player1->get_lives() << std::endl;
                }

                music1->play_effect();
                apple_vec.erase(apple_vec.begin()+i);

            }

        }

    }

    //CHECK APPLE BELOW PLAYER//LOSING LIFE
    if(apple_vec.size() > 0){
        for(unsigned int i=0; i<apple_vec.size(); i++){
            if( apple_vec[i]->get_rect()->y > player1->get_rect()->y+player1->get_rect()->h){

                std::cout << "Apple missed!" << std::endl;
                if(apple_vec[i]->get_special()){
                    std::cout << "It was special!" << std::endl;
                }else{
                    std::cout << "It was regular!" << std::endl;
                    player1->lose_life();
                }

                apple_vec.erase(apple_vec.begin()+i);

                if(player1->get_lives() == 0){
                    std::cout << "Game over!" << std::endl;
                    //not_started = true;
                    reset_game();
                    menu_stack.push(mainmenu1);
                }
            }
        }
    }

    //SPAWN APPLES
    apple_counter++;
    if(apple_counter == counter_limit){
        spawn_apple();
        apple_counter = 0;
        counter_limit = rand()%45+26; //spawn apple at 30-70 frames
    }else if(apple_counter == 20){
        spawn_special();
    }

}

//DRAW BACKGROUND
void game::show_background(){

    SDL_RenderCopy(renderer, background_texture, NULL, &background_rect);
}

void game::menu_system(Uint32 start){

    start = SDL_GetTicks();

    menu_stack.top()->show_menu(renderer);
    if(mouse_click == true){
        //std::cout << "mouse click registered" << std::endl;
        menu_stack.top()->action(menu_stack,mouse_x,mouse_y);
        mouse_click = false;
    }
    handle_events();
    SDL_RenderPresent(renderer);

    regulate_fps(start);
}

void game::reset_game(){

    apple_vec.clear();

    apple_counter = 0;
    counter_limit = 45;

    player1->set_x_pos(60);
    player1->set_lives(1);
}

//Main game
void game::start(){

    Uint32 start;
    srand(time(0));

    music1->play_music();

    menu_stack.push(mainmenu1);

    //Main game loop
    while(is_running){

        while(!menu_stack.empty()){
            //title_menu(start);
            menu_system(start);

        }

        start = SDL_GetTicks();
        handle_events();
        show_background();
        game_logic();

        SDL_RenderPresent(renderer);
        regulate_fps(start);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


