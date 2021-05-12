#pragma once
#include <vector>

#include "Engine.h"
#include "Scene.h"
#include "Gui.h"
#include "MultiTileObject.h"
#include "Level.h"

#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

#include "ECS.h"
#include "Animation.h"

class SceneThree :
    public Scene
{
public:

    SceneThree(Engine* engine);

    void init(Engine* engine);
    void processInput();
    void update(const float dt);
    void render(const float dt);
    void cleanup();

private:
    //imgui flags
    bool _debugtile_ = false;
    bool _debugui_ = false;
    bool check_im = false;
    bool check_inf = true;
    bool check_ttp = false;
    bool eop = false;
    bool check_comt = true;
    bool check_hitb = true;
    //

    sf::View game_view;
    sf::View hud_view;

    sf::Sprite sprite;
    std::vector<sf::Sprite> sprite_bg;
    sf::Texture texture;
    sf::Texture texture_bg;
    sf::Vector2f mouse_p;
    sf::Vector2f view_pos;

    Level level;

    MultiTileObject mtocell1;
    MultiTileObject mtocell2;
    MultiTileObject mtocell3;
    MultiTileObject mtocell4;

    _MTO_sprite_info spr_info;
    _MTO_texture_indexes mto_index;
    _MTO_texture_info tex_info;

    ECS::Entity player;
    ECS::Entity enemy;

    AnimationManager anim_manager;
    Animation anim;

    float x;
    float x_vel;
    float x_acs;

    void updateUi(sf::Vector2f pos);
};

