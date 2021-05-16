#pragma once

#include "Types.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "EventManager.h"

namespace ECS
{
    class Coordinator
    {
    private:
        std::unique_ptr<ComponentManager> mComponentManager;
        std::unique_ptr<EntityManager> mEntityManager;
        std::unique_ptr<SystemManager> mSystemManager;
        std::unique_ptr<EventManager> mEventManager;

    public:
        void Init()
        {
            mComponentManager = std::make_unique<ComponentManager>();
            mEntityManager = std::make_unique<EntityManager>();
            mEventManager = std::make_unique<EventManager>();
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

        //EVENT METHODS
        void AddEventListener(EventId eventId, std::function<void(Event&)> const& listener)
        {
            mEventManager->AddListener(eventId, listener);
        }

        void SendEvent(Event& event)
        {
            mEventManager->SendEvent(event);
        }

        void SendEvent(EventId eventId)
        {
            mEventManager->SendEvent(eventId);
        }

        //DEBUG
        uint32_t getLivingEntity()
        {
            return mEntityManager->getLivingEntity();
        }
    };
}

