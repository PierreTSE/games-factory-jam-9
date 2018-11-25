#include "RessourceLoader.hpp"
#include <filesystem>


RessourceReference<sf::Texture> RessourceLoader::getTexture(std::string const& name)
{
    if(ressourceLoaderInstance.loadedTextures.find(name) != ressourceLoaderInstance.loadedTextures.end())
        return ressourceLoaderInstance.loadedTextures[name].get();
    else 
        return ressourceLoaderInstance.loadTexture(name);
}

RessourceReference<sf::Texture> RessourceLoader::loadTexture(std::string const& name)
{
    std::string path = getPath(name);
    auto tex = std::make_unique<sf::Texture>();
    tex->loadFromFile(path);
    return loadedTextures.insert({name, std::move(tex)}).first->second.get();
}

std::string RessourceLoader::getPath(std::string const& name)
{
    if(!ressourceLoaderInstance.wdSet)
    {
        using namespace std::filesystem;
        path p = current_path();
        while(!exists(p/"rc") && p.has_parent_path())
            p = p.parent_path();
        if(exists(p/"rc"))
            current_path(p);
        else
            throw std::runtime_error("Can't find resources directory");
        ressourceLoaderInstance.wdSet = true;
    }
    return "rc/"+name;
}

RessourceReference<sf::SoundBuffer> RessourceLoader::getSound(std::string const& name)
{
    if(ressourceLoaderInstance.loadedSound.find(name) != ressourceLoaderInstance.loadedSound.end())
        return ressourceLoaderInstance.loadedSound[name].get();
    else
        return ressourceLoaderInstance.loadSound(name);
}

RessourceReference<sf::SoundBuffer> RessourceLoader::loadSound(std::string const& name)
{
    std::string path = getPath(name);
    auto snd = std::make_unique<sf::SoundBuffer>();
    snd->loadFromFile(path);
    return loadedSound.insert({name, std::move(snd)}).first->second.get();
}
