#include"DJ.hpp"
#include <filesystem>
#include "RessourceLoader.hpp"
#include <iostream>

DJ::DJ()
{
    std::filesystem::path dirPath = RessourceLoader::getPath("audio");

    if(!std::filesystem::is_directory(dirPath))
        throw std::runtime_error("Not a directory" + dirPath.u8string());

    for(auto& file : std::filesystem::directory_iterator(dirPath))
    {
        if(file.path().extension() == ".wav")
        {
            soundBuffers_.emplace_back();
            if(!soundBuffers_.back().loadFromFile(file.path().string()))
                std::cerr << file.path().u8string() << std::endl;

            sounds_[file.path().filename().string()] = sf::Sound(soundBuffers_.back());
        }
        else if(file.path().extension() == ".ogg")
        {
            musics_[file.path().filename().string()] = std::make_unique<sf::Music>();
            musics_[file.path().filename().string()]->openFromFile(file.path().string());
        }
    }
}

DJ& DJ::getInstance() { return DJInstance; }

void DJ::playSound(const std::string& name) { sounds_[name].play(); }
                    
void DJ::playMusic(const std::string& name) { musics_[name]->play(); }
                    
void DJ::stopMusic(const std::string& name) { musics_[name]->stop(); }
