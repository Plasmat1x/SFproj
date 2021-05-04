#pragma once
#include <vector>

#include "Engine.h"
#include "Scene.h"
#include "Gui.h"
#include "MultiTileObject.h"

#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

class SceneOne :
    public Scene
{
public:

    SceneOne(Engine* engine);

    void init(Engine* engine);
    void processInput();
    void update(const float dt);
    void render(const float dt);
    void cleanup();

private:
    std::map<std::string, Gui> guiSys;

    sf::Sprite sprite;
    sf::Sprite ico;
    sf::Texture tex;
    sf::Texture tex_ico;
    sf::Texture tex_button;

    _MTO_sprite_info spr_info;
    _MTO_sprite_info spr_info_two;
    _MTO_texture_indexes mto_index;
    _MTO_texture_indexes mto_index_two;
    _MTO_texture_info tex_info;

    MultiTileObject mto_sprite;
    MultiTileObject mto_sprite_two;

};

