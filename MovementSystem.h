#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H
#include <math.h>

extern GameEngine gameEngine;

class MovementSystem : public System
{
public:
    void Update(float dt, sf::RenderWindow& window) override
    {
        Signature movementSignature = gameEngine.GetSystemSignature<MovementSystem>();
        for (int i = 0; i < MAX_ENTITIES; ++i)
        {
            if ((gameEngine.GetEntityMask(i) & movementSignature) == movementSignature)
            {
                InputComponent& inputComponent = gameEngine.GetComponent<InputComponent>(i);
                PositionComponent& positionComponent = gameEngine.GetComponent<PositionComponent>(i);
                RigidbodyComponent& rigidbodyComponent = gameEngine.GetComponent<RigidbodyComponent>(i);
                AnimationComponent& animationComponent = gameEngine.GetComponent<AnimationComponent>(i);
                GravityComponent& gravityComponent = gameEngine.GetComponent<GravityComponent>(i);
                
                animationComponent.row = IDEAL;
                
                if(inputComponent.dir == RIGHT)
                {
                    positionComponent.x += rigidbodyComponent.speed * dt;
                    animationComponent.row = RUNNING;
                    animationComponent.faceRight = true;
                }
                
                if(inputComponent.dir == LEFT)
                {
                    positionComponent.x -= rigidbodyComponent.speed * dt;
                    animationComponent.row = RUNNING;
                    animationComponent.faceRight = false;
                }
                
                if(inputComponent.parallelDir == SPACE && rigidbodyComponent.canJump)
                {
                    rigidbodyComponent.velocity.y = -sqrt(2.0f * gravityComponent.force * rigidbodyComponent.jumpHeight);
                    rigidbodyComponent.canJump = false;
                }
            }
        }
    }
};


#endif

