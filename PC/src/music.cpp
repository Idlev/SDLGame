#include "music.h"

music::music()
{
    //Open audio channels,freq,format,chunk size
    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);

    game_music = Mix_LoadMUS("mus.mp3");
    if(game_music == NULL)
        std::cout << "Error loading music." << std::endl;

    effect_apple = Mix_LoadWAV("apple.wav");
    if(effect_apple == NULL)
        std::cout << "Error loading effect." << std::endl;

    Mix_VolumeMusic(MIX_MAX_VOLUME/4);
    Mix_Volume(1,MIX_MAX_VOLUME/4);

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

