#pragma once
#include <vector>

#include "Engine.h"
#include "Scene.h"
#include "Entity.h"
#include "Button.h"

class SceneTwo : 
    public Scene
{
public:

    void init();
    void cleanup();

    void pause();
    void resume();

    void processInput(Engine* engine);
    void update(Engine* engine);
    void render(Engine* engine);

    static SceneTwo* instance() { return &m_SceneTwo; }

protected:
    SceneTwo() {}

private:
    std::vector<Entity*> objects;

    static SceneTwo m_SceneTwo;
};

