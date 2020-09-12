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

    //mouse test
    enum mouseInput
    {
        Left,
        Right,
        Count
    };

    bool mInputs[2] = {false, false};
    bool mPrevInputs[2] = { false, false };

    bool Released(mouseInput key);
    bool KeyState(mouseInput key);
    bool Pressed(mouseInput key);

    void updatePrevInputs();
};

