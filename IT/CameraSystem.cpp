#include "CameraSystem.h"
#include "Coordinator.h"
#include "COM_LIB.h"

extern ECS::Coordinator gCoordinator;

void SYS::CameraSystem::update()
{
    for (auto const& entity : mEntities)
    {
        auto& View = gCoordinator.GetComponent<COM::View>(entity);
        auto& Transform = gCoordinator.GetComponent<COM::Transform>(entity);

        View.view->setCenter(Transform.position.x, Transform.position.y);
    }
}