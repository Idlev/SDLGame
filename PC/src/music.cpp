#include "music.h"

music::music()
{
    level_music = 16;
    level_effect = 16;
    interval = 8;

    //Open audio channels,freq,format,chunk size
    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);

    game_music = Mix_LoadMUS("mus.mp3");
    if(game_music == NULL)
        std::cout << "Error loading music." << std::endl;

    effect_apple = Mix_LoadWAV("apple.wav");
    if(effect_apple == NULL)
        std::cout << "Error loading effect." << std::endl;

    Mix_VolumeMusic(level_music);
    Mix_Volume(1,level_effect);

}

music::~music()
{
    Mix_FreeMusic(game_music);
    Mix_FreeChunk(effect_apple);
    Mix_CloseAudio();
}

void music::play_music(){

    //Infinite loop
    Mix_PlayMusic(game_music,-1);

}

void music::play_effect(){

    //Play effect once
    Mix_PlayChannel(1,effect_apple,0);
}

int music::get_music_vol(){

    return level_music;
}

int music::get_effect_vol(){

    return level_effect;
}

void music::raise_music(){

    std::cout << "RAISE MUSIC VOLUME, ";

    level_music += interval;

    if(level_music >= 128){
        level_music = 128;
    }

    Mix_VolumeMusic(level_music);
    std::cout << "NOW AT: " << level_music << std::endl;
}

void music::lower_music(){

    std::cout << "LOWER MUSIC VOLUME, ";

    level_music -= interval;

    if(level_music <= 0){
        level_music = 0;
    }

    Mix_VolumeMusic(level_music);
    std::cout << "NOW AT: " << level_music << std::endl;
}

void music::raise_effect(){

    std::cout << "RAISE EFFECT VOLUME, ";

    level_effect += interval;

    if(level_effect >= 128){
        level_effect = 128;
    }

    Mix_Volume(1,level_effect);
    std::cout << "NOW AT: " << level_effect << std::endl;
    play_effect();
}

void music::lower_effect(){

    std::cout << "LOWER EFFECT VOLUME, ";

    level_effect -= interval;

    if(level_effect <= 0){
        level_effect = 0;
    }

    Mix_Volume(1,level_effect);
    play_effect();
    std::cout << "NOW AT: " << level_effect << std::endl;

}
