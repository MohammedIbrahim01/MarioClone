#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "Utils.h"
#include "GameEngine.h"
#include "CollisionComponent.h"
#include "TileComponent.h"
#include "AnimationComponent.h"


class Map
{
public:
    static void Load(GameEngine& gameEngine, std::string mapInfoFile, std::string levelFile)
    {
        ReadMapInfo(mapInfoFile);
        LoadLevel(gameEngine, levelFile);
    }
    
    static void AddTile(GameEngine& gameEngine, int tileIndex, float posX, float posY)
    {
        sf::Vector2u tileHalfSize;
        if (tileIndex == 5)
        {
            tileHalfSize.x = 104/2;
            tileHalfSize.y = 128/2;
        }
        else if (tileIndex == 6)
        {
            tileHalfSize.x = 32/2;
            tileHalfSize.y = 480/2;
        }
        else 
        {
            tileHalfSize.x = mapInfo[TILE_WIDTH]/2;
            tileHalfSize.y = mapInfo[TILE_HEIGHT]/2;
        }
        

        int newTile = gameEngine.CreateEntity();
        gameEngine.AddComponent<PositionComponent>(newTile, PositionComponent{tileHalfSize.x + posX, tileHalfSize.y + posY});
        std::shared_ptr<sf::Sprite> pSprite = std::make_shared<sf::Sprite>(tileTextures[tileIndex-1]);
        pSprite->setOrigin(tileHalfSize.x, tileHalfSize.y);
        gameEngine.AddComponent<RenderComponent>(newTile, RenderComponent{pSprite});
        gameEngine.AddComponent<CollisionComponent>(newTile, CollisionComponent{1, tileHalfSize});
        if(tileIndex == 3)
        {
            gameEngine.AddComponent<TileComponent>(newTile, TileComponent{COIN_TILE});
            gameEngine.AddComponent<AnimationComponent>(newTile, AnimationComponent{32, 32, 1});
        }
        else if (tileIndex == 2)
        {
            gameEngine.AddComponent<TileComponent>(newTile, TileComponent{WALL_TILE});
        }
        else if (tileIndex == 6)
        {
            gameEngine.AddComponent<TileComponent>(newTile, TileComponent{FLAG_TILE});
        }
    }
    
    
    static void ReadMapInfo(std::string mapInfoFileName)
    {
        std::fstream mapInfoFile;
        mapInfoFile.open(mapInfoFileName);
        
        mapInfoFile.ignore(1000, '\n');         // ignore the first line (usage line)
        
        std::string str1, str2;
        getline(mapInfoFile, str1);
        std::stringstream ss(str1);

        for(int i = 0; i < MAP_INFO_NUM; ++i)
        {
            getline(ss, str2, ',');
            mapInfo[i] = stoi(str2);
        }
        
        for (int i = 0; i < mapInfo[TEXTURE_NUM]; i++)
        {
            std::string texturePath;
            getline(mapInfoFile, texturePath);
            tileTextures.push_back(Utils::LoadTexture(texturePath));
        }
        
        mapInfoFile.close();
    }
    
    static void LoadLevel(GameEngine& gameEngine, std::string levelFileName)
    {
        std::fstream levelFile;
        levelFile.open(levelFileName);
        assert(levelFile.is_open());
        

        for (int i = 0; i < mapInfo[VERTICAL_TILE_NUM]; i++)
        {
            for (int j = 0; j < mapInfo[HORIZONTAL_TILE_NUM]; j++)
            {
                char c;
                levelFile.get(c);   // tile index
                levelFile.ignore(); // comma ',' or '\n' at the end of each raw
                int tileIndex = atoi(&c);
                
                if (tileIndex == 0)
                    continue;


                AddTile(gameEngine, tileIndex, j*mapInfo[TILE_WIDTH], i*mapInfo[TILE_HEIGHT]);
            }
        }

        levelFile.close();
    }
    
private:
    enum mapInfoIndexes {HORIZONTAL_TILE_NUM, VERTICAL_TILE_NUM, TILE_WIDTH, TILE_HEIGHT, TEXTURE_NUM, MAP_INFO_NUM};
    static int mapInfo[MAP_INFO_NUM];
    static std::vector<sf::Texture> tileTextures;
};

int Map::mapInfo[MAP_INFO_NUM];
std::vector<sf::Texture> Map::tileTextures;

#endif
