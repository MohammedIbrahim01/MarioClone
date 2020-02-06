#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <iostream>
#include <array>
#include <queue>
#include <memory>
#include <bitset>
#include <unordered_map>
#include "Types.h"
#include "System.h"
#include "ComponentArray.h"


class GameEngine
{
public:
    GameEngine() = default;
    ~GameEngine() = default;

    void Init()
    {
        // populate available entities
        for (int i = 0; i < MAX_ENTITIES; ++i)
        {
            mAvialableEntities.push(i);
        }
    }
    
    Entity CreateEntity()
    {
        // get entity from available entities
        Entity entity = mAvialableEntities.front();
        mAvialableEntities.pop();
        
        std::cout << "entity created : " << entity << "\n";
        
        return entity;
    }
    
    void DisableEntity(int entity)
    {
        // reset the entity mask so no system will run on its components
        mEntityMasks[entity].reset();
    }
    
    template<typename T>
    void RegisterComponent()
    {
        // register new component type by store an id tied to its typeName in map
        std::string typeName = typeid(T).name();
        mComponentTypes.insert({typeName, mNextComponentType});
        ++mNextComponentType;
        
        // create new componentArray of this new component
        mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
    }

    template<typename T>
    void AddComponent(Entity entity, T component)
    {
        std::string typeName = typeid(T).name();
        
        ComponentType componentType = GetComponentType<T>();
        mEntityMasks[entity].set(componentType);
        
        GetComponentArray<T>(typeName)->Add(entity, component);
    }
    
    template<typename T>
    T& GetComponent(Entity entity)
    {
        std::string typeName = typeid(T).name();
        
        return GetComponentArray<T>(typeName)->Get(entity);
    }
    
    template<typename T>
    bool HasComponent(int entity)
    {
        std::string typeName = typeid(T).name();
        
        int componentType = GetComponentType<T>();
        return mEntityMasks[entity].test(componentType);
    }
    
    template<typename T>
    ComponentType GetComponentType()
    {
        std::string typeName = typeid(T).name();
        
        return mComponentTypes[typeName];
    }
    
    template<typename T>
    void RegisterSystem()
    {
        std::string typeName = typeid(T).name();
        
        mSystems.insert({typeName, std::make_shared<T>()});
    }
    
    template<typename T>
    void SetSystemSignature(Signature signature)
    {
        std::string typeName = typeid(T).name();
        
        mSystemSignatures.insert({typeName, signature});
    }
    
    template<typename T>
    Signature GetSystemSignature()
    {
        std::string typeName = typeid(T).name();
        
        return mSystemSignatures[typeName];
    }
    
    Signature GetEntityMask(int index)
    {
        return mEntityMasks[index];
    }
    
    void SetPlayerEntity(int entity)
    {
        playerEntity = entity;
    }
    
    Entity GetPlayerEntity()
    {
        return playerEntity;
    }
    
    void Update(float dt, sf::RenderWindow& window)
    {
        for (auto& pair : mSystems)
        {
            auto& system = pair.second;
            system->Update(dt, window);
        }
    }
    
    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray(std::string typeName)
    {
        return std::static_pointer_cast<ComponentArray<T>> (mComponentArrays[typeName]);
    }
    

private:
    Entity playerEntity;
    
    std::array<Signature, MAX_ENTITIES> mEntityMasks;
    
    std::queue<Entity> mAvialableEntities;
    std::unordered_map<std::string, std::shared_ptr<IComponentArray>> mComponentArrays;

    std::unordered_map<std::string, ComponentType> mComponentTypes;
    std::unordered_map<std::string, Signature> mSystemSignatures;

    std::unordered_map<std::string, std::shared_ptr<System>> mSystems;
    int mNextComponentType = 0;
};


#endif

