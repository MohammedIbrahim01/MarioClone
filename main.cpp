#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include "Ui.h"
#include "PositionComponent.h"
#include "RenderComponent.h"
#include "GravityComponent.h"
#include "GravitySystem.h"
#include "RenderSystem.h"
#include "Utils.h"
#include "Map.h"
#include "InputComponent.h"
#include "RigidbodyComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"
#include "TileComponent.h"
#include "MovementSystem.h"
#include "InputSystem.h"
#include "AnimationSystem.h"
#include "CollisionSystem.h"

using namespace std;

GameEngine gameEngine;
Ui ui;

void AddStaticTile(GameEngine& gameEngine, std::shared_ptr<sf::Sprite> pSprite, float posX, float posY)
{
    int newTile = gameEngine.CreateEntity();
    gameEngine.AddComponent<PositionComponent>(newTile, PositionComponent{posX, posY});
    gameEngine.AddComponent<RenderComponent>(newTile, RenderComponent{pSprite});
}

void AddGravityTile(GameEngine& gameEngine, std::shared_ptr<sf::Sprite> pSprite, float posX, float posY, float gForce)
{
    int newTile = gameEngine.CreateEntity();
    gameEngine.AddComponent<PositionComponent>(newTile, PositionComponent{posX, posY});
    gameEngine.AddComponent<RenderComponent>(newTile, RenderComponent{pSprite});
    gameEngine.AddComponent<GravityComponent>(newTile, GravityComponent{gForce});
}

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(800, 640), "Super Mario Clone");
    sf::View view(sf::FloatRect(0, 0, 800, 640));
    
    
    gameEngine.Init();
    ui.Init("assets/default_font.ttf");
    
    gameEngine.RegisterComponent<PositionComponent>();
    gameEngine.RegisterComponent<RenderComponent>();
    gameEngine.RegisterComponent<GravityComponent>();
    gameEngine.RegisterComponent<InputComponent>();
    gameEngine.RegisterComponent<RigidbodyComponent>();
    gameEngine.RegisterComponent<AnimationComponent>();
    gameEngine.RegisterComponent<CollisionComponent>();
    gameEngine.RegisterComponent<TileComponent>();
    
    gameEngine.RegisterSystem<RenderSystem>();
    {
        Signature signature;
        signature.set(gameEngine.GetComponentType<PositionComponent>());
        signature.set(gameEngine.GetComponentType<RenderComponent>());
        gameEngine.SetSystemSignature<RenderSystem>(signature);
    }
    
    gameEngine.RegisterSystem<GravitySystem>();
    {
        Signature signature;
        signature.set(gameEngine.GetComponentType<PositionComponent>());
        signature.set(gameEngine.GetComponentType<GravityComponent>());
        signature.set(gameEngine.GetComponentType<RigidbodyComponent>());
        gameEngine.SetSystemSignature<GravitySystem>(signature);
    }
    gameEngine.RegisterSystem<InputSystem>();
    {
        Signature signature;
        signature.set(gameEngine.GetComponentType<InputComponent>());
        gameEngine.SetSystemSignature<InputSystem>(signature);
    }
    gameEngine.RegisterSystem<MovementSystem>();
    {
        Signature signature;
        signature.set(gameEngine.GetComponentType<PositionComponent>());
        signature.set(gameEngine.GetComponentType<InputComponent>());
        signature.set(gameEngine.GetComponentType<RigidbodyComponent>());
        gameEngine.SetSystemSignature<MovementSystem>(signature);
    }
    gameEngine.RegisterSystem<AnimationSystem>();
    {
        Signature signature;
        signature.set(gameEngine.GetComponentType<RenderComponent>());
        signature.set(gameEngine.GetComponentType<AnimationComponent>());
        gameEngine.SetSystemSignature<AnimationSystem>(signature);
    }
    
    gameEngine.RegisterSystem<CollisionSystem>();
    {
        Signature signature;
        signature.set(gameEngine.GetComponentType<PositionComponent>());
        signature.set(gameEngine.GetComponentType<CollisionComponent>());
        gameEngine.SetSystemSignature<CollisionSystem>(signature);
    }
    
    Map::Load(gameEngine, "map_info/map_info.txt", "map_info/level2.txt");
    
    
    int mario = gameEngine.CreateEntity();
    gameEngine.SetPlayerEntity(mario);
    gameEngine.AddComponent<InputComponent>(mario, InputComponent{});
    gameEngine.AddComponent<RigidbodyComponent>(mario, RigidbodyComponent{250, 200, true});
    std::shared_ptr<sf::Sprite> pSprite = std::make_shared<sf::Sprite>(Utils::LoadTexture("assets/mario_sheet.png"));
    pSprite->setOrigin(16, 32);
    gameEngine.AddComponent<RenderComponent>(mario, RenderComponent{pSprite});
    gameEngine.AddComponent<PositionComponent>(mario, PositionComponent{100, 100});
    gameEngine.AddComponent<GravityComponent>(mario, GravityComponent{true, 980});
    gameEngine.AddComponent<AnimationComponent>(mario, AnimationComponent{32, 65, 3, 0.1});
    gameEngine.AddComponent<CollisionComponent>(mario, CollisionComponent{0, sf::Vector2u(16, 32)});
    
    
    float totalTime = 0;
    float dt = 0;
    sf::Clock clock;
    while(window.isOpen())
    {
        dt = clock.restart().asSeconds();
        
        totalTime += dt;
        if (totalTime - ui.GetTime() >= 1)
            ui.IncreaseTimeBy(1);
        
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
                window.close();
        }
        
        float playerPosX = gameEngine.GetComponent<PositionComponent>(gameEngine.GetPlayerEntity()).x;
        if (playerPosX + 200 > 400)
        {
            view.setCenter(playerPosX + 200, 320);
            window.setView(view);
        }
        ui.SetPosition(view.getCenter().x - 400);
        
        window.clear(sf::Color(102, 178, 255));         // clear with light blue color
        
        gameEngine.Update(dt, window);
        ui.Draw(window);
        
        window.display();
    }
    
    return 0;
}