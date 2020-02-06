#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H


extern GameEngine gameEngine;


class RenderSystem : public System
{
public:
    void Update(float dt, sf::RenderWindow& window) override
    {
        Signature renderSignature = gameEngine.GetSystemSignature<RenderSystem>();
        for (int i = 0; i < MAX_ENTITIES; ++i)
        {
            if ((gameEngine.GetEntityMask(i) & renderSignature) == renderSignature)
            {
                RenderComponent& renderComponent = gameEngine.GetComponent<RenderComponent>(i);
                PositionComponent& positionComponent = gameEngine.GetComponent<PositionComponent>(i);
                
                renderComponent.pSprite->setPosition(positionComponent.x, positionComponent.y);
            
                window.draw(*renderComponent.pSprite);
            }
        }
    }
};

#endif

