#pragma once
#include "Engine.h"

class Scene
{
public:
    virtual void init(Engine* engine) = 0;
    virtual void processInput() = 0;
    virtual void update(const float dt) = 0;
    virtual void render(const float dt) = 0;
    virtual void cleanup() = 0;

    Engine* engine;
    sf::Event* event;
    sf::View* view;
};


