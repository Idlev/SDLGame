#include "optionsmenu.h"

optionsmenu::optionsmenu(SDL_Texture *menu_tex, SDL_Texture *bg_tex, SDL_Texture *vol_tex, music *mus) : menu(menu_tex, bg_tex)
{
    rect_effect_plus.x = BLANK_X+91;
    rect_effect_plus.y = BLANK_Y+74;
    rect_effect_plus.w = 10;
    rect_effect_plus.h = 11;

    rect_effect_minus.x = BLANK_X+20;
    rect_effect_minus.y = BLANK_Y+74;
    rect_effect_minus.w = 10;
    rect_effect_minus.h = 11;

    rect_music_plus.x = BLANK_X+91;
    rect_music_plus.y = BLANK_Y+49;
    rect_music_plus.w = 10;
    rect_music_plus.h = 11;

    rect_music_minus.x = BLANK_X+21;
    rect_music_minus.y = BLANK_Y+49;
    rect_music_minus.w = 10;
    rect_music_minus.h = 11;

    volume_texture = vol_tex;
    music1 = mus;

    //Create target rects to present volume magnitude
    for(int i=0; i<16; i++){

        music_clips[i].x = BLANK_X+44+i*VOLUME_WIDTH;
        music_clips[i].y = BLANK_Y+52;
        music_clips[i].w = VOLUME_WIDTH;
        music_clips[i].h = VOLUME_HEIGHT;

        effect_clips[i].x = BLANK_X+44+i*VOLUME_WIDTH;
        effect_clips[i].y = BLANK_Y+77;
        effect_clips[i].w = VOLUME_WIDTH;
        effect_clips[i].h = VOLUME_HEIGHT;
    }
}

optionsmenu::~optionsmenu()
{
    //dtor
}

void optionsmenu::save_data(){

    std::ifstream in("init.txt");
    std::ofstream out("out.txt");

    if( !in || !out){

        std::cout << "Unable to open files!" << std::endl;
        return;
    }

    std::string tmp;

    while(std::getline(in,tmp)){

        std::cout << "LINE IN: " << tmp << std::endl;

        if(tmp[0] == 'M'){
            std::cout << "MUSIC_VOL: " << music1->get_music_vol() << std::endl;
            tmp = "M" + std::to_string(music1->get_music_vol());
        }else if(tmp[0] == 'E'){
            std::cout << "EFFECT VOL: " << music1->get_effect_vol() << std::endl;
            tmp = "E"+std::to_string(music1->get_effect_vol());
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

void optionsmenu::show_menu(SDL_Renderer *renderer){

    SDL_RenderCopy(renderer, bg_texture, NULL, &bg_rect);
    SDL_RenderCopy(renderer, menu_texture, NULL, &menu_rect);

    for(int i=0; i<16; i++){

        if(i*8 < music1->get_music_vol() or (music1->get_music_vol() == 128 and i*8 == 128))
            SDL_RenderCopy(renderer,volume_texture,NULL,&music_clips[i]);

        if(i*8 < music1->get_effect_vol() )
            SDL_RenderCopy(renderer,volume_texture,NULL,&effect_clips[i]);

    }
}

int optionsmenu::action(std::stack<menu*> &stack_menu, int x, int y){

    int ans = 1;

    std::cout << "OPTIONSMENU ACTION:" << std::endl;

    //CHECK IF MOUSE COORDINARES INSIDE MENU BOXES

    if( check_cursor(x,y,rect_return) ){
        save_data();
        pop_menu(stack_menu);
    }else if( check_cursor(x,y,rect_music_plus) ){
        music1->raise_music();
    }else if( check_cursor(x,y,rect_music_minus) ){
        music1->lower_music();
    }else if( check_cursor(x,y,rect_effect_plus) ){
        music1->raise_effect();
    }else if( check_cursor(x,y,rect_effect_minus) ){
        music1->lower_effect();
    }

    return ans;
}
