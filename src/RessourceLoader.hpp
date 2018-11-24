#ifndef RESSOURCELOADER_HPP
#define RESSOURCELOADER_HPP


#include <vector>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <map>


template<typename T>
struct RessourceReference
{
    RessourceReference(T& t) : data{&t} {}
    RessourceReference(T* pt) : data{pt} {}
    RessourceReference& operator=(T& t) { data = &t; return *this; }
    RessourceReference& operator=(T* pt) { data = pt; return *this; }
    
    operator T&() { return *data; }
    
    T* data = nullptr;
};

class RessourceLoader
{
    public:
        static RessourceReference<sf::Texture> getTexture(std::string const& name);
    
    private:
        RessourceReference<sf::Texture> loadTexture(std::string const& name);
        std::string getPath(std::string const& name);
    
        bool wdSet = false;
        std::map<std::string, std::unique_ptr<sf::Texture>> loadedTextures;
        std::map<std::string, std::unique_ptr<sf::SoundBuffer>> loadedSound;
};

static RessourceLoader ressourceLoaderInstance;


#endif // RESSOURCELOADER_HPP