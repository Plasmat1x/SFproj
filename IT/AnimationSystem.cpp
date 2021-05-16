#include "AnimationSystem.h"
#include "Coordinator.h"
#include "COM_LIB.h"

extern ECS::Coordinator gCoordinator;

void SYS::AnimationSystem::playAnimation(ECS::Entity entity, std::string name)
{
    auto animation = gCoordinator.GetComponent<COM::Anim>(entity);
    auto sprite = gCoordinator.GetComponent<COM::Sprite>(entity).sprite;

    animation.anim->play(&sprite, animation.mgr->getAnimation(name));
}
