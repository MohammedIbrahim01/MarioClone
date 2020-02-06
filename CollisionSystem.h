#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "TileComponent.h"
#include "AnimationComponent.h"
#include "GameEngine.h"
#include "Ui.h"


extern GameEngine gameEngine;
extern Ui ui;

void hitCoin(Entity i);
void hitWall(Entity i);

class CollisionSystem : public System
{
    enum CollisionDirections {NONE, RIGHT, LEFT, TOP, DOWN};
public:
    void Update(float dt, sf::RenderWindow& window) override
    {
        int playerEntity = gameEngine.GetPlayerEntity();
        PositionComponent& playerPositionComponent = gameEngine.GetComponent<PositionComponent>(playerEntity);
        CollisionComponent& playerCollisionComponent = gameEngine.GetComponent<CollisionComponent>(playerEntity);
        GravityComponent& playerGravityComponent = gameEngine.GetComponent<GravityComponent>(playerEntity);
        RigidbodyComponent& playerRigidbodyComponent = gameEngine.GetComponent<RigidbodyComponent>(playerEntity);
        
        Signature collisionSignature = gameEngine.GetSystemSignature<CollisionSystem>();
        for (int i = 0; i < MAX_ENTITIES && i != playerEntity; ++i)
        {
            if ((gameEngine.GetEntityMask(i) & collisionSignature) == collisionSignature)
            {
                PositionComponent& positionComponent = gameEngine.GetComponent<PositionComponent>(i);
                CollisionComponent& collisionComponent = gameEngine.GetComponent<CollisionComponent>(i);
             
                float deltaX = positionComponent.x - playerPositionComponent.x;
                float deltaY = positionComponent.y - playerPositionComponent.y;
                
                float intersectX = fabs(deltaX) - (playerCollisionComponent.halfSize.x + collisionComponent.halfSize.x);
                float intersectY = fabs(deltaY) - (playerCollisionComponent.halfSize.y + collisionComponent.halfSize.y);
                
                
                int collisionDir = NONE;
                if (intersectX < 0 && intersectY < 0)
                {
                    if (intersectX > intersectY)
                    {
                        if (deltaX > 0)
                        {
                            positionComponent.x += -intersectX * playerCollisionComponent.push;
                            playerPositionComponent.x += intersectX * (1 - playerCollisionComponent.push);
                            
                            collisionDir = RIGHT;
                        }
                        else
                        {
                            positionComponent.x += intersectX * playerCollisionComponent.push; 
                            playerPositionComponent.x += -intersectX * (1 - playerCollisionComponent.push);
                            
                            collisionDir = LEFT;
                        }
                    }
                    else
                    {
                        if (deltaY > 0)
                        {
                            positionComponent.y += -intersectY * playerCollisionComponent.push;
                            playerPositionComponent.y += intersectY * (1 - playerCollisionComponent.push);
                            
                            collisionDir = DOWN;
                        }
                        else
                        {
                            positionComponent.y += intersectY * playerCollisionComponent.push;
                            playerPositionComponent.y += -intersectY * (1 - playerCollisionComponent.push);
                            
                            collisionDir = TOP;
                        }
                    }
                }
                
                if (collisionDir == DOWN)
                {
                    playerGravityComponent.enable = false;
                    playerRigidbodyComponent.velocity.y = 0;
                    playerRigidbodyComponent.canJump = true;
                }
                else if (collisionDir == TOP)
                {
                    playerRigidbodyComponent.velocity.y = 0;
                    if (gameEngine.HasComponent<TileComponent>(i))
                    {
                        TileComponent& tileComponent = gameEngine.GetComponent<TileComponent>(i);
                        if (tileComponent.type == COIN_TILE)
                        {
                            hitCoin(i);
                        }
                        else if (tileComponent.type == WALL_TILE)
                        {
                            hitWall(i);
                        }
                    }
                }
                else if (collisionDir == RIGHT)
                {
                    if (gameEngine.HasComponent<TileComponent>(i))
                    {
                        TileComponent& tileComponent = gameEngine.GetComponent<TileComponent>(i);
                        if (tileComponent.type == FLAG_TILE)
                        {
                            playerPositionComponent.x = 100;
                            playerPositionComponent.y = 100;
                            
                            sf::sleep(sf::seconds(2));
                            
                            ComponentArray<AnimationComponent>& animationArray = *gameEngine.GetComponentArray<AnimationComponent>(typeid(AnimationComponent).name());
                            for (int i = 0; i < MAX_ENTITIES; i++)
                            {
                                animationArray.Get(i).row = IDEAL;
                            }
                        }
                    }
                }
                else if (collisionDir == NONE)
                {
                    playerGravityComponent.enable = true;
                }
            }
        }
    }
};


void hitCoin(Entity i)
{
    gameEngine.GetComponent<AnimationComponent>(i).row = EMPTY;
    ui.IncreaseCoinsBy(1);
    ui.IncreaseScoreBy(10);
}

void hitWall(Entity i)
{
    gameEngine.DisableEntity(i);
}

#endif

