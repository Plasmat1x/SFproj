#pragma once
#include <vector>

#include "Engine.h"
#include "Scene.h"
#include "Entity.h"
#include "Button.h"

class SceneOne :
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

    static SceneOne* instance() { return &m_SceneOne; }
protected:
    SceneOne() {}

private:
    std::vector<Button*> objects;
    static SceneOne m_SceneOne;
};

