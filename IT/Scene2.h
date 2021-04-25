#pragma once
#include <vector>

#include "Engine.h"
#include "Scene.h"
#include "Gui.h"
#include "MultiTileObject.h"

#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

#include "_GUI.h"

class SceneTwo :
    public Scene
{
public:

    SceneTwo(Engine* engine);

    void init(Engine* engine);
    void processInput();
    void update(const float dt);
    void render(const float dt);
    void cleanup();

private:
    std::map<std::string, Gui> guiSys;

    MultiTileObject mto;
    MultiTileObject mto_;
    bool mto_pos;
    sf::Vector2f buf;

    GUI_container container;
    GUI_container container_child;
};

