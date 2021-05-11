#include "RenderSystem.h"
#include "Coordinator.h"
#include "COM_LIB.h"

extern ECS::Coordinator gCoordinator;

void SYS::RenderSystem::updateAnim()
{
    for (auto const& entity : mEntities)
    {
        auto& Sprite = gCoordinator.GetComponent<COM::Sprite>(entity);
        auto& Anim = gCoordinator.GetComponent<COM::Anim>(entity);
        auto& States = gCoordinator.GetComponent<COM::States>(entity);
        
        if (Anim.anim != nullptr && Anim.mgr != nullptr)
        {
            const auto& anim_map = Anim.mgr->getAnimMap();

            for (const auto& [anim_name, anim] : anim_map)
            {
                for (const auto& [state_name, state] : States.states)
                {
                    if (strcmp(state_name.c_str(), "direction") == 0)
                    {
                        dir = state;
                    }
                    std::string st_nm = "";
                    if (dir)
                    {
                        st_nm = state_name;
                    }
                    else
                    {
                        st_nm = state_name + "f";
                    }
                    if (strcmp(anim_name.c_str(), st_nm.c_str()) == 0)
                    {
                        if (state)
                        {
                            Anim.anim->play(&Sprite.sprite, Anim.mgr->getAnimation(st_nm));
                            return;
                        }
                    }
                }
            }

        }
    }
}

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