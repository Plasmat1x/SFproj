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

    MultiTileObject mto_;

    _MTO_sprite_info spr_info;
    _MTO_sprite_info spr_info_two;
    _MTO_texture_indexes mto_index;
    _MTO_texture_indexes mto_index_two;
    _MTO_texture_info tex_info;

    MultiTileObject mto_sprite;
    MultiTileObject mto_sprite_two;

    bool mto_pos;
    //sf::Vector2f buf;

    GUI_container container;
    GUI_container container_child;

    std::ostringstream oss;

    CORE_Config buf;
};

