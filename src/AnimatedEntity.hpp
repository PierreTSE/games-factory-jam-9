#ifndef ANIMATEDENTITY_HPP
#define ANIMATEDENTITY_HPP


#include <type_traits>
#include <map>
#include "animatedSprite.hpp"
#include <SFML/Graphics/RenderTarget.hpp>





template<typename StateType>
    class AnimatedEntity : public sf::Transformable
{
    static_assert(std::is_enum_v<StateType>, "AnimatedEntity is expecting an enum type to describe its possible states");
    
    public:
        AnimatedEntity(StateType defaultState, AnimatedSprite const& sprite);
        void setup(StateType state, AnimatedSprite const& sprite);
        void setState(StateType state);
        
        void draw(sf::RenderTarget&);
    
    private:
        AnimatedSprite* currentSprite();
    
        StateType current;
        std::vector<StateType> states;
        std::vector<AnimatedSprite> sprites;
};


template<typename StateType>
void AnimatedEntity<StateType>::setState(StateType state)
{
    if(current == state)
        return;
    ptrdiff_t index = std::find(states.begin(), states.end(), current) - states.begin();
    if(index < states.size())
        sprites[index].reset();
    current = state;
}

template<typename StateType>
void AnimatedEntity<StateType>::setup(StateType state, AnimatedSprite const& sprite)
{
    states.push_back(state);
    sprites.push_back(sprite);
}

template<typename StateType>
AnimatedEntity<StateType>::AnimatedEntity(StateType defaultState, AnimatedSprite const& sprite)
{
    setup(defaultState, sprite);
    current = defaultState;
}

template<typename StateType>
void AnimatedEntity<StateType>::draw(sf::RenderTarget& target)
{
    auto c = currentSprite();
    if(!c)
        return;
    AnimatedSprite& curSprite = *c;
    curSprite.update();
    curSprite.setOrigin(getOrigin());
    curSprite.setPosition(getPosition());
    curSprite.setRotation(getRotation());
    curSprite.setScale(getScale());

    target.draw(curSprite);
}

template<typename StateType>
AnimatedSprite* AnimatedEntity<StateType>::currentSprite()
{
    ptrdiff_t index = std::find(states.begin(), states.end(), current) - states.begin();
    return index < states.size() ? &sprites[index] : nullptr;
}

#endif // ANIMATEDENTITY_HPP