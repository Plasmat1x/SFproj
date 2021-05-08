/*
https://austinmorlan.com/posts/entity_component_system/

//Coordinator usage:

Entity player = coordinator.CreateEntity();
coordinator.AddComponent<Transform>(player);
RenderSystem renderSystem = coordinator.RegisterSystem<RenderSystem>();





//We have the following components:

struct Gravity
{
    Vec3 force;
};

struct RigidBody
{
    Vec3 velocity;
    Vec3 acceleration;
};

struct Transform
{
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
};


//A system for rudimentary physics integration:
Each system can then inherit from this class which allows the System Manager 
to keep a list of pointers to systems. Inheritance, but not virtual.

extern Coordinator gCoordinator;

void PhysicsSystem::Update(float dt)
{
    for (auto const& entity : mEntities)
    {
        auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
        auto& transform = gCoordinator.GetComponent<Transform>(entity);
        auto const& gravity = gCoordinator.GetComponent<Gravity>(entity);

        transform.position += rigidBody.velocity * dt;

        rigidBody.velocity += gravity.force * dt;
    }
}



//Then the main loop:

Coordinator gCoordinator;

int main()
{
    gCoordinator.Init();

    gCoordinator.RegisterComponent<Gravity>();
    gCoordinator.RegisterComponent<RigidBody>();
    gCoordinator.RegisterComponent<Transform>();

    auto physicsSystem = gCoordinator.RegisterSystem<PhysicsSystem>();

    Signature signature;
    signature.set(gCoordinator.GetComponentType<Gravity>());
    signature.set(gCoordinator.GetComponentType<RigidBody>());
    signature.set(gCoordinator.GetComponentType<Transform>());
    gCoordinator.SetSystemSignature<PhysicsSystem>(signature);

    std::vector<Entity> entities(MAX_ENTITIES);

    std::default_random_engine generator;
    std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
    std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
    std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
    std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

    float scale = randScale(generator);

    for (auto& entity : entities)
    {
        entity = gCoordinator.CreateEntity();

        gCoordinator.AddComponent(
            entity,
            Gravity{Vec3(0.0f, randGravity(generator), 0.0f)});

        gCoordinator.AddComponent(
            entity,
            RigidBody{
                .velocity = Vec3(0.0f, 0.0f, 0.0f),
                .acceleration = Vec3(0.0f, 0.0f, 0.0f)
            });

        gCoordinator.AddComponent(
            entity,
            Transform{
                .position = Vec3(randPosition(generator), randPosition(generator), randPosition(generator)),
                .rotation = Vec3(randRotation(generator), randRotation(generator), randRotation(generator)),
                .scale = Vec3(scale, scale, scale)
            });
    }

    float dt = 0.0f;

    while (!quit)
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        physicsSystem->Update(dt);

        auto stopTime = std::chrono::high_resolution_clock::now();

        dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
    }
}

*/






/*
usage in code:

init()
{
    gCoordinator.Init();

    gCoordinator.RegisterComponent<COM::Position>();
    gCoordinator.RegisterComponent<COM::Velocity>();

    // also can make shared_ptr<T> as global for use in different func;
    auto physicsSystem = gCoordinator.RegisterSystem<SYS::PhysicSystem>();

    ECS::Signature signature;
    signature.set(gCoordinator.GetComponentType<COM::Position>());
    signature.set(gCoordinator.GetComponentType<COM::Velocity>());
    gCoordinator.SetSystemSignature<SYS::PhysicSystem>(signature);

    player = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<COM::Position>(player, { 1.0f, 1.0f });
    gCoordinator.AddComponent<COM::Velocity>(player, { 10.0f, 10.0f });
}

update()
{

    physicsSystem->update(dt);
    
    std::cout << "\r" << std::setw(16) <<
                int(gCoordinator.GetComponent<COM::Position>(player).x) << "       " <<
                int(gCoordinator.GetComponent<COM::Position>(player).y);

}
*/