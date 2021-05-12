#pragma once
#include <functional>
#include <list>
#include <unordered_map>

#include "Event.h"
#include "Types.h"

namespace ECS
{
    class EventManager
    {
    private:
        std::unordered_map<EventId, std::list<std::function<void(Event&)>>> listeners;

    public:
        void AddListener(EventId eventId, std::function<void(Event&)> const& listener)
        {
            listeners[eventId].push_back(listener);
        }

        void SendEvent(Event event)
        {
            uint32_t type = event.GetType();

            for (auto const& listener : listeners[type])
            {
                listener(event);
            }
        }

        void SendEvent(EventId eventId)
        {
            Event event(eventId);

            for (auto const& listener : listeners[eventId])
            {
                listener(event);
            }
        }
    };
}