#pragma once
#include <memory>
#include <cassert>
#include <unordered_map>
#include <utility>

#include "Types.h"
#include "System.h"

namespace ECS
{
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
}
