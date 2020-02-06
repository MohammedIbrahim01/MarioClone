#ifndef GRAVITYSYSTEM_H
#define GRAVITYSYSTEM_H

#include "RigidbodyComponent.h"


extern GameEngine gameEngine;

class GravitySystem : public System
{
public:
    void Update(float dt, sf::RenderWindow& window) override
    {
        Signature physicsSignature = gameEngine.GetSystemSignature<GravitySystem>();
        for (int i = 0; i < MAX_ENTITIES; ++i)
        {
            if ((gameEngine.GetEntityMask(i) & physicsSignature) == physicsSignature)
            {
                PositionComponent& positionComponent = gameEngine.GetComponent<PositionComponent>(i);
                GravityComponent& gravityComponent = gameEngine.GetComponent<GravityComponent>(i);
                RigidbodyComponent& rigidbodyComponent = gameEngine.GetComponent<RigidbodyComponent>(i);
            
                positionComponent.y += rigidbodyComponent.velocity.y * dt;
                rigidbodyComponent.velocity.y += gravityComponent.force * dt;
            }
        }
    }
};


#endif

