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

    //SCORE
    score = 0;
    highscore = 0;

    //10 Numbers
    for(int i=0; i<10; i++){

        score_clips[i].x = i*SCORE_WIDTH;
        score_clips[i].y = 0;
        score_clips[i].w = SCORE_WIDTH;
        score_clips[i].h = SCORE_HEIGHT;
    }

    //3 Digits for score
    for(int i=0; i<3; i++){

        score_rects[i].x = 49 + i*(SCORE_WIDTH+1);
        score_rects[i].y = 0;
        score_rects[i].w = SCORE_WIDTH;
        score_rects[i].h = SCORE_HEIGHT;

        //score_rects[i].x = score_rects[i].x+1;
    }

    //SCALE
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
    menu_image = load_image("menu3.png");
    menu_texture = SDL_CreateTextureFromSurface(renderer,menu_image);
    options_image = load_image("options4.png");
    options_texture = SDL_CreateTextureFromSurface(renderer,options_image);
    scoremenu_image = load_image("highscore2.png");
    scoremenu_texture = SDL_CreateTextureFromSurface(renderer,scoremenu_image);

    player_image = load_image("PlayerFrames.png");
    player_texture = SDL_CreateTextureFromSurface(renderer, player_image);
    lives_image = load_image("extralife.png");
    lives_texture = SDL_CreateTextureFromSurface(renderer, lives_image);

    apple_image = load_image("apple6.png");
    apple_texture = SDL_CreateTextureFromSurface(renderer, apple_image);
    apple_sp_image = load_image("applesp.png");
    apple_sp_texture = SDL_CreateTextureFromSurface(renderer,apple_sp_image);

    volume_image = load_image("volume2.png");
    volume_texture = SDL_CreateTextureFromSurface(renderer,volume_image);

    score_image = load_image("nums.png");
    highscore_image = load_image("numshigh.png");
    score_texture = SDL_CreateTextureFromSurface(renderer,score_image);
    highscore_texture = SDL_CreateTextureFromSurface(renderer,highscore_image);


    player1 = new player(player_texture,lives_texture);
    music1 = new music();
    scoremenu1 = new scoremenu(scoremenu_texture,title_bg_texture,highscore_texture);
    optionsmenu1 = new optionsmenu(options_texture,title_bg_texture,volume_texture,music1);
    mainmenu1 = new mainmenu(menu_texture,title_bg_texture,optionsmenu1,scoremenu1);
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
    SDL_DestroyTexture(score_texture);
    SDL_DestroyTexture(highscore_texture);
    SDL_DestroyTexture(scoremenu_texture);

    SDL_FreeSurface(player_image);
    SDL_FreeSurface(apple_image);
    SDL_FreeSurface(apple_sp_image);
    SDL_FreeSurface(title_bg_image);
    SDL_FreeSurface(menu_image);
    SDL_FreeSurface(volume_image);
    SDL_FreeSurface(score_image);
    SDL_FreeSurface(highscore_image);
    SDL_FreeSurface(scoremenu_image);

}

//IMAGE LOAD FUNCTION FOR PLAYER, BACKGROUND, APPLES
SDL_Surface *game::load_image(const char *filename){

    SDL_Surface *tmp = IMG_Load(filename);

    if(tmp == NULL)
        std::cout << "Error loading image" << std::endl;

    return tmp;
}

//Read data from savefile
bool game::read_data(const char *filename){

    //open file
    std::ifstream in(filename);

    if(!in){
        std::cout << "Unable to open file: " << filename << std::endl;
        return false;
    }

    std::string tmp;
    while(std::getline(in,tmp)){

        //If line has text, save it
        if(tmp.size() > 0)
            data_vec.push_back(tmp);
    }

    //Close file
    in.close();

    return true;
}

void game::save_data(){

    std::ifstream in("init.txt");
    std::ofstream out("out.txt");

    if( !in || !out){

        std::cout << "Unable to open files!" << std::endl;
        return;
    }

    std::string tmp;

    while(std::getline(in,tmp)){

        std::cout << "LINE IN: " << tmp << std::endl;

        if(tmp[0] == 'S'){
            tmp = "S" + std::to_string(highscore);
        }

        tmp += "\n";

        std::cout << "LINE OUT: " << tmp << std::endl;

        out << tmp;

    }

    in.close();
    out.close();

    remove("init.txt");
    rename("out.txt","init.txt");


}


//Act on saved data
//Highscore, music volume, effect volume
void game::apply_data(){

    std::string tmp;
    //int val;

    for(int i=0; i<data_vec.size(); i++){

        tmp = data_vec[i];

        if(tmp[0] == '#'){
            continue;
        }else if(tmp[0] == 'S'){
            tmp.erase(0,1);
            highscore = std::stoi(tmp);
            scoremenu1->update_highscore(highscore);
        }else if(tmp[0] == 'M'){
            tmp.erase(0,1);
            music1->set_music_vol(std::stoi(tmp));
            std::cout << "MUSIC NOW: " << music1->get_music_vol() << std::endl;
        }else if(tmp[0] == 'E'){
            tmp.erase(0,1);
            music1->set_effect_vol(std::stoi(tmp));
            std::cout << "EFFECT NOW: " << music1->get_effect_vol() << std::endl;
        }

    }

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
                SDL_Quit();
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

//SPAWN SPECIAL
void game::spawn_special(){

    if(rand()%25 == 0)
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
    show_score();

    //CHECK APPLE PLAYER COLLISION
    if(apple_vec.size() > 0){
        for(unsigned int i=0; i<apple_vec.size(); i++){
            if(check_collision(player1->get_coll_rect(),apple_vec[i]->get_coll_rect())){
                std::cout << "Caught an apple!" << std::endl;

                if(apple_vec[i]->get_special()){
                    std::cout << "SPECIAL CAUGHT" << std::endl;
                    player1->gain_life();
                    std::cout << "Curr lives: " << player1->get_lives() << std::endl;
                }else{
                    score++;
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

                if(player1->get_lives() == 0){
                    std::cout << "Game over!" << std::endl;
                    show_lose();
                    menu_stack.push(mainmenu1);
                    reset_game();
                    break;
                }

                apple_vec.erase(apple_vec.begin()+i);
            }
        }
    }

    //SPAWN APPLES
    apple_counter++;
    if(apple_counter == counter_limit){
        spawn_apple();
        apple_counter = 0;
        counter_limit = rand()%45+26; //spawn apple at 30-70 frames
    }else if(apple_counter == 20 and player1->get_lives() < 2){
            spawn_special();
    }

}

//LOSING ANIMATION
void game::show_lose(){

    Uint32 start;
    int tmp = 0;

    while(tmp < 70){

        start = SDL_GetTicks();

        show_background();
        show_score();

        //SHOW PLAYER BLINK
        if( (tmp >= 0 and tmp < 10) or (tmp >= 20 and tmp <= 30) or
            (tmp >= 40 and tmp <= 50) or (tmp > 60 and tmp <= 70) ){
            player1->show_player(renderer);
        }

        //SHOW APPLES
        if(apple_vec.size() > 0){
            for(unsigned int i=0; i<apple_vec.size(); i++){
                apple_vec[i]->show_apple(renderer);
            }
        }

        SDL_RenderPresent(renderer);
        regulate_fps(start);

        tmp++;
    }
}

//DRAW BACKGROUND
void game::show_background(){

    SDL_RenderCopy(renderer, background_texture, NULL, &background_rect);
}

//DRAW CURRENT SCORE
void game::show_score(){

    std::string tmp = std::to_string(score);

    for(int i=0; i<tmp.length(); i++){

        if(tmp[i] == '0'){
            SDL_RenderCopy(renderer, score_texture, &score_clips[0], &score_rects[i]);
            continue;
        }else if(tmp[i] == '1'){
            SDL_RenderCopy(renderer, score_texture, &score_clips[1], &score_rects[i]);
            continue;
        }else if(tmp[i] == '2'){
            SDL_RenderCopy(renderer, score_texture, &score_clips[2], &score_rects[i]);
            continue;
        }else if(tmp[i] == '3'){
            SDL_RenderCopy(renderer, score_texture, &score_clips[3], &score_rects[i]);
            continue;
        }else if(tmp[i] == '4'){
            SDL_RenderCopy(renderer, score_texture, &score_clips[4], &score_rects[i]);
            continue;
        }else if(tmp[i] == '5'){
            SDL_RenderCopy(renderer, score_texture, &score_clips[5], &score_rects[i]);
            continue;
        }else if(tmp[i] == '6'){
            SDL_RenderCopy(renderer, score_texture, &score_clips[6], &score_rects[i]);
            continue;
        }else if(tmp[i] == '7'){
            SDL_RenderCopy(renderer, score_texture, &score_clips[7], &score_rects[i]);
            continue;
        }else if(tmp[i] == '8'){
            SDL_RenderCopy(renderer, score_texture, &score_clips[8], &score_rects[i]);
            continue;
        }else if(tmp[i] == '9'){
            SDL_RenderCopy(renderer, score_texture, &score_clips[9], &score_rects[i]);
            continue;
        }
    }

}

void game::menu_system(Uint32 start){

    start = SDL_GetTicks();

    menu_stack.top()->show_menu(renderer);
    if(mouse_click == true){
        //std::cout << "mouse click registered" << std::endl;
        if(menu_stack.top()->action(menu_stack,mouse_x,mouse_y) == 0)
           is_running = false;

        mouse_click = false;
    }

    handle_events();
    SDL_RenderPresent(renderer);

    regulate_fps(start);
}

void game::reset_game(){

    apple_vec.clear();

    if(score > highscore){
        highscore = score;
        scoremenu1->update_highscore(highscore);

        save_data();

        std::cout << "HIGHSCORE: " << scoremenu1->get_highscore() << std::endl;
        menu_stack.push(scoremenu1);
    }

    score = 0;
    apple_counter = 0;
    counter_limit = 45;

    player1->set_x_pos(60);
    player1->set_lives(1);

}

//Main game
void game::start(){

    Uint32 start;
    srand(time(0));

    read_data("init.txt");

    //apply saved data
    apply_data();

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

