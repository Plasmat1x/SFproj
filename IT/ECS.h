#pragma once
#include<stdlib.h>
#include<utility>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<cassert>
#include<bitset>
#include<array>
#include<memory>
#include<set>

namespace ECS
{

    using Entity = uint64_t;
    const Entity MAX_ENTITIES = 5000;

    using COM_type = uint8_t;
    const COM_type MAX_COMS = 32;

    using Signature = std::bitset<MAX_COMS>;

    class EntityManager
    {
    private:
        std::queue<Entity> mAvailableEntities{};
        std::array<Signature, MAX_ENTITIES> mSignatures{};

        uint32_t mLivingEntityCount{};

    public:
        EntityManager()
        {
            for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
            {
                mAvailableEntities.push(entity);
            }
        }

        Entity CreateEntity()
        {
            assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existance.");

            Entity id = mAvailableEntities.front();
            mAvailableEntities.pop();
            ++mLivingEntityCount;

            return id;
        }

        void DestroyEntity(Entity entity)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            mSignatures[entity].reset();

            mAvailableEntities.push(entity);
            --mLivingEntityCount;
        }

        void SetSignature(Entity entity, Signature signature)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            mSignatures[entity] = signature;
        }

        Signature GetSignature(Entity entity)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            return mSignatures[entity];
        }

    };

    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;
    };

    template<class T>
    class ComponentArray : public IComponentArray
    {
    private:
        std::array<T, MAX_ENTITIES> mComponentArray;
        std::unordered_map<Entity, size_t> mEntityToIndexMap;
        std::unordered_map<size_t, Entity> mIndexToEntityMap;

        size_t mSize;
    public:

        void InsertData(Entity entity, T component)
        {
            assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

            size_t newIndex = mSize;
            mEntityToIndexMap[entity] = newIndex;
            mIndexToEntityMap[newIndex] = entity;
            mComponentArray[newIndex] = component;
            ++mSize;
        }

        void RemoveData(Entity entity)
        {
            assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");

            size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
            size_t indexOfLastElement = mSize - 1;
            mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

            Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
            mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            mEntityToIndexMap.erase(entity);
            mIndexToEntityMap.erase(indexOfLastElement);

            --mSize;
        }

        T& GetData(Entity entity)
        {
            assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");

            return mComponentArray[mEntityToIndexMap[entity]];
        }

        void EntityDestroyed(Entity entity) override
        {
            if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
            {
                RemoveData(entity);
            }
        }
    };

    class ComponentManager
    {
    private:

        std::unordered_map<const char*, COM_type> mComponentTypes{};
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};

        COM_type mNextComponentType{};

        template<typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray()
        {
            const char* typeName = typeid(T).name();

            assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registred before use.");

            return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
        }

    public:
        template<typename T>
        void RegisterComponent()
        {
            const char* typeName = typeid(T).name();

            assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");

            mComponentTypes.insert({ typeName, mNextComponentType });

            mComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

            ++mNextComponentType;
        }

        template<typename T>
        COM_type GetComponentType()
        {
            const char* typeName = typeid(T).name();

            assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registred before use.");

            return mComponentTypes[typeName];
        }

        template<typename T>
        void AddComponent(Entity entity, T component)
        {
            GetComponentArray<T>()->InsertData(entity, component);
        }

        template<typename T>
        void RemoveComponent(Entity entity)
        {
            GetComponentArray<T>()->RemoveData(entity);
        }

        template<typename T>
        T& GetComponent(Entity entity)
        {
            return GetComponentArray<T>()->GetData(entity);
        }

        void EntityDestroyed(Entity entity)
        {
            for (auto const& pair : mComponentArrays)
            {
                auto const& component = pair.second;

                component->EntityDestroyed(entity);
            }
        }
    };

    class System
    {
    public:
        std::set<Entity> mEntities;
    };

    class SystemManager
    {
    private:
        std::unordered_map<const char*, Signature> mSignatures{};
        std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};

    public:

        template<typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            const char* typeName = typeid(T).name();

            assert(mSystems.find(typeName) == mSystems.end() && "Registering system more then once");

            auto system = std::make_shared<T>();
            mSystems.insert({ typeName, system });
            return system;
        }

        template<typename T>
        void SetSignature(Signature signature)
        {
            const char* typeName = typeid(T).name();

            assert(mSystems.find(typeName) != mSystems.end() && "System used before register");

            mSignatures.insert({ typeName, signature });
        }

        void EntityDestroyed(Entity entity)
        {
            for (auto const& pair : mSystems)
            {
                auto const& system = pair.second;

                system->mEntities.erase(entity);
            }
        }

        void EntitySignatureChanged(Entity entity, Signature entitySignature)
        {
            for (auto const& pair : mSystems)
            {
                auto const& type = pair.first;
                auto const& system = pair.second;
                auto const& systemSignature = mSignatures[type];

                if ((entitySignature & systemSignature) == systemSignature)
                {
                    system->mEntities.insert(entity);
                }
                else
                {
                    system->mEntities.erase(entity);
                }
            }
        }
    };

    class Coordinator
    {
    private:
        std::unique_ptr<ComponentManager> mComponentManager;
        std::unique_ptr<EntityManager> mEntityManager;
        std::unique_ptr<SystemManager> mSystemManager;

    public:
        void Init()
        {
            mComponentManager = std::make_unique<ComponentManager>();
            mEntityManager = std::make_unique<EntityManager>();
            mSystemManager = std::make_unique<SystemManager>();
        }

        //ENTITY METHODS
        Entity CreateEntity()
        {
            return mEntityManager->CreateEntity();
        }

        void DestroyEntity(Entity entity)
        {
            mEntityManager->DestroyEntity(entity);
            mComponentManager->EntityDestroyed(entity);
            mSystemManager->EntityDestroyed(entity);
        }

        //COM METHODS
        template<typename T>
        void RegisterComponent()
        {
            mComponentManager->RegisterComponent<T>();
        }

        template<typename T>
        void AddComponent(Entity entity, T component)
        {
            mComponentManager->AddComponent<T>(entity, component);

            auto signature = mEntityManager->GetSignature(entity);
            signature.set(mComponentManager->GetComponentType<T>(), true);
            mEntityManager->SetSignature(entity, signature);

            mSystemManager->EntitySignatureChanged(entity, signature);
        }

        template<typename T>
        void RemoveComponent(Entity entity)
        {
            mComponentManager->RemoveComponent<T>(entity);

            auto signature = mEntityManager->GetSignature(entity);
            signature.set(mComponentManager->GetComponentType<T>(), false);
            mEntityManager->SetSignature(entity, signature);

            mSystemManager->EntitySignatureChanged(entity, signature);
        }

        template<typename T>
        T& GetComponent(Entity entity)
        {
            return mComponentManager->GetComponent<T>(entity);
        }

        template<typename T>
        COM_type GetComponentType()
        {
            return mComponentManager->GetComponentType<T>();
        }

        //SYSTEM METHODS
        template<typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            return mSystemManager->RegisterSystem<T>();
        }

        template<typename T>
        void SetSystemSignature(Signature signature)
        {
            mSystemManager->SetSignature<T>(signature);
        }
    };
}
