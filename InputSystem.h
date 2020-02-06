#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H
#include <SFML/Window/Keyboard.hpp>


class InputSystem : public System
{
    public:
        void Update(float dt, sf::RenderWindow& window) override
        {
            Signature inputSignature = gameEngine.GetSystemSignature<InputSystem>();
            for (int i = 0; i < MAX_ENTITIES; ++i)
            {
                if ((gameEngine.GetEntityMask(i) & inputSignature) == inputSignature)
                {
                    InputComponent& inputComponent = gameEngine.GetComponent<InputComponent>(i);
                    
                    inputComponent.dir = NONE;
                    inputComponent.parallelDir = NONE;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                        inputComponent.dir = RIGHT;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                        inputComponent.dir = LEFT;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        inputComponent.dir = UP;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        inputComponent.dir = DOWN;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                        inputComponent.parallelDir = SPACE;
                }
            }
        }
};


#endif

