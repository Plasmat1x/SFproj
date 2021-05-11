#include "RenderSystem.h"
#include "Coordinator.h"
#include "COM_LIB.h"

extern ECS::Coordinator gCoordinator;

void SYS::RenderSystem::draw(sf::RenderWindow& window)
{
    for (auto const& entity : mEntities)
    {
        auto& Sprite = gCoordinator.GetComponent<COM::Sprite>(entity);
        auto& Position = gCoordinator.GetComponent<COM::Transform>(entity);
        auto& Rect = gCoordinator.GetComponent<COM::Hitbox>(entity);

        Sprite.sprite.setPosition(Position.position.x, Position.position.y);

        window.draw(Sprite.sprite);

        if (Rect.draw)
        {
            window.draw(Rect.shape);
        }

    }
}