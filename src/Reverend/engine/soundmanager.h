#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <iostream>
#include <map>
#include <string>
#include "SDL/SDL_mixer.h"

enum SoundType
{
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager
{
public:
    
    static SoundManager& getInstance()
    {
		static SoundManager instance_;
        return instance_;
    }
    
    bool load(std::string fileName, std::string id, SoundType type);
    
    void playSound(std::string id, int loop);
    void playMusic(std::string id, int loop);
    
private:
    
    std::map<std::string, Mix_Chunk*> m_sfxs;
    std::map<std::string, Mix_Music*> m_music;
    
    SoundManager();
    ~SoundManager();
    
};

typedef SoundManager SoundManager;

#endif