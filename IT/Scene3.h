#pragma once
#include <vector>
#include <box2d/box2d.h>

#include "Engine.h"
#include "Scene.h"
#include "Gui.h"
#include "MultiTileObject.h"
#include "Level.h"

#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

#include "Types.h"
#include "Animation.h"
#include "Player.h"
#include "ParallaxBackground.h"

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
    //ECS Event
    //std::bitset<8> mButtons;

    //imgui flags
    bool _debugtile_ = false;
    bool _debugui_ = false;
    bool check_im = false;
    bool check_inf = true;
    bool check_ttp = false;
    bool eop = false;
    bool check_comt = true;
    bool check_hitb = true;
    bool check_ecs = false;
    bool check_sum_info = true;
    //
    float time = 0.f;
    float view_zoom_factor = 0.5f;
    //float view_zoom_factor = 2;

    bool _pause = false;

    sf::View game_view;
    sf::View hud_view;

    sf::Sprite sprite;
    std::vector<sf::Sprite> sprite_bg;
    sf::Texture texture;
    sf::Texture texture_bg;
    sf::Texture bg;
    sf::Sprite sbg;
    sf::Vector2f mouse_p;
    sf::Vector2f view_pos;

    Level level;
    ParallaxBackground back_ground;

    MultiTileObject mtocell1;
    MultiTileObject mtocell2;
    MultiTileObject mtocell3;
    MultiTileObject mtocell4;

    MultiTileObject mto_sprite;
    MultiTileObject mto_sprite_two;

    _MTO_sprite_info spr_info;
    _MTO_sprite_info spr_info_two;
    _MTO_texture_indexes mto_index;
    _MTO_texture_indexes mto_index_two;
    _MTO_texture_info tex_info;


    //ECS::Entity player;
    ECS::Entity enemy;
    ECS::Entity cur_ent;

    AnimationManager anim_manager;
    Animation anim;

    Player player;

    std::map<std::string, Gui> guiSys;

    void updateUi(const float dt);

};

