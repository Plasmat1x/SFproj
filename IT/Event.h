#pragma once
#include <any>
#include <unordered_map>

#include "Types.h"

namespace ECS
{
    class Event
    {
    private:
        EventId mType{};
        std::unordered_map<EventId, std::any> mData{};

    public:
        Event() = delete;

        explicit Event(EventId type)
            :mType(type)
        {}
        
        template<typename T>
        void SetParam(EventId id, T value)
        {
            mData[id] = value;
        }

        template<typename T>
        T GetParam(EventId id)
        {
            return std::any_cast<T>(mData[id]);
        }

        EventId GetType() const
        {
            return mType;
        }
    };
}