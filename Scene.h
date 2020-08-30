#pragma once
#include "Engine.h"

class Scene
{
public:
    virtual void init() = 0;
    virtual void cleanup() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void processInput(Engine* engine) = 0;
    virtual void update(Engine* engine) = 0;
    virtual void render(Engine* engine) = 0;

    void changeScene(Engine* engine, Scene* scene) { engine->changeScene(scene); }
    
protected:
    Scene() {}
};

