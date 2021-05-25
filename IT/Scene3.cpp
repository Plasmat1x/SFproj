#include <iostream>
#include <cmath>
#include "ResourceManager.h"
#include "Scene3.h"
#include "dGrid.h"

#include "COM_LIB.h"
#include "SYS_LIB.h"

extern ECS::Coordinator gCoordinator;

std::shared_ptr<SYS::PhysicsSystem> physicsSystem;
std::shared_ptr<SYS::RenderSystem> renderSystem;
std::shared_ptr<SYS::CameraSystem> cameraSystem;
std::shared_ptr<SYS::InputSystem> inputSystem;

SceneThree::SceneThree(Engine* engine)
{
    init(engine);
}

void SceneThree::init(Engine* engine)
{
    x = 0; x_vel = 0; x_acs = 2;

    this->engine = engine;
    this->event = &engine->events;
    this->view = &engine->view;
    this->game_view = engine->view;
    this->hud_view = engine->view;

    this->game_view.zoom(0.5f);

    //view setup
    sf::Vector2f pos = sf::Vector2f(this->engine->window.getSize());
    this->view->setSize(pos);
    pos *= 0.5f;
    this->view->setCenter(pos);

    this->hud_view.setCenter(pos);

    ResourceManager::loadTexture("tile_set", "map.png");
    ResourceManager::loadTexture("bg_sky", "sky.png");
    ResourceManager::loadTexture("bg_clouds", "clouds.png");
    ResourceManager::loadTexture("bg_sea", "sea.png");
    ResourceManager::loadTexture("bg_far-grounds", "far-grounds.png");

    texture.loadFromFile("../res/img/elf.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 43, 60));

    texture_bg.loadFromFile("../res/img/map.png");
    bg.loadFromFile("../res/img/sky.png");
    bg.setRepeated(false);
    sbg.setTexture(bg);
    sbg.setTextureRect(sf::IntRect(0, 32 * 10, 32 * 64, 32 * 26));
    sbg.setPosition(0, 0);

    //level load
    level = Level("../res/map/test_level.tmx", &texture_bg, sf::Vector2i(10, 10));

    // setup multitile
    mto_index = _MTO_texture_indexes({
        sf::Vector2i(3,0),
        sf::Vector2i(4,0),
        sf::Vector2i(5,0),
        sf::Vector2i(3,1),
        sf::Vector2i(4,1),
        sf::Vector2i(5,1),
        sf::Vector2i(3,2),
        sf::Vector2i(4,2),
        sf::Vector2i(5,2) });

    tex_info = {
        ResourceManager::getTexture("test_ui"),                     // texture
        sf::Vector2f(8.0f,8.0f),                                    // element size
        sf::Vector2f(1.0f,1.0f),                                    // padding
        sf::Vector2f(1.0f,1.0f),                                    // offset
        sf::Vector2i(6,3)                                           // texture array size
    };

    spr_info = {
        sf::Vector2f(pos.x, pos.y),                                 // position
        sf::Vector2f(64, 64.0f),                                    // size
        sf::Vector2f(1.0f, 1.0f),                                   // scale
        sf::Vector2f(32.0f, 32.0f),                                 // origin
        sf::Vector2f(1.0f, 1.0f),                                   // add_scale
    };

    mtocell1 = MultiTileObject(
        &tex_info,
        &spr_info,
        &mto_index
    );

    mtocell2 = MultiTileObject(
        &tex_info,
        &spr_info,
        &mto_index
    );

    mtocell3 = MultiTileObject(
        &tex_info,
        &spr_info,
        &mto_index
    );

    mtocell4 = MultiTileObject(
        &tex_info,
        &spr_info,
        &mto_index
    );

    //Бутафорный UI
    sf::Vector2f uipos = pos;
    mtocell1.setPosition(sf::Vector2f(uipos.x - 96, uipos.y * 1.9f));
    mtocell2.setPosition(sf::Vector2f(uipos.x - 32, uipos.y * 1.9f));
    mtocell3.setPosition(sf::Vector2f(uipos.x + 32, uipos.y * 1.9f));
    mtocell4.setPosition(sf::Vector2f(uipos.x + 96, uipos.y * 1.9f));


    //ECS
    gCoordinator.Init();

    gCoordinator.RegisterComponent<COM::Transform>();
    gCoordinator.RegisterComponent<COM::RigidBody>();
    gCoordinator.RegisterComponent<COM::Sprite>();
    gCoordinator.RegisterComponent<COM::View>();
    gCoordinator.RegisterComponent<COM::Input>();
    gCoordinator.RegisterComponent<COM::Hitbox>();
    gCoordinator.RegisterComponent<COM::Anim>();
    gCoordinator.RegisterComponent<COM::States>();

    //Physic
    physicsSystem = gCoordinator.RegisterSystem<SYS::PhysicsSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<COM::Transform>());
        signature.set(gCoordinator.GetComponentType<COM::RigidBody>());
        signature.set(gCoordinator.GetComponentType<COM::Hitbox>());
        signature.set(gCoordinator.GetComponentType<COM::States>());
        gCoordinator.SetSystemSignature<SYS::PhysicsSystem>(signature);
    } physicsSystem->init(&level);

    //Render
    renderSystem = gCoordinator.RegisterSystem<SYS::RenderSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<COM::Transform>());
        signature.set(gCoordinator.GetComponentType<COM::Sprite>());
        signature.set(gCoordinator.GetComponentType<COM::Hitbox>());
        signature.set(gCoordinator.GetComponentType<COM::Anim>());
        signature.set(gCoordinator.GetComponentType<COM::States>());
        gCoordinator.SetSystemSignature<SYS::RenderSystem>(signature);
    }

    //View
    cameraSystem = gCoordinator.RegisterSystem<SYS::CameraSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<COM::Transform>());
        signature.set(gCoordinator.GetComponentType<COM::View>());
        gCoordinator.SetSystemSignature<SYS::CameraSystem>(signature);
    }

    //Control
    inputSystem = gCoordinator.RegisterSystem<SYS::InputSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<COM::Input>());
        signature.set(gCoordinator.GetComponentType<COM::RigidBody>());
        signature.set(gCoordinator.GetComponentType<COM::States>());
        gCoordinator.SetSystemSignature<SYS::InputSystem>(signature);
    }

    //debug rect for hitbox
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color(0xff, 0xff, 0xff, 0x00));
    rect.setOutlineColor(sf::Color(0xff, 0xff, 0x88, 0xff));
    rect.setOutlineThickness(1.0f);
    rect.setSize(sf::Vector2f(43, 60));
    rect.setPosition(sf::Vector2f(64,64));

    //create entity 
    enemy = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<COM::Transform>(enemy, { sf::Vector2f(64,64), sf::Vector2f(1,1), 0 });
    gCoordinator.AddComponent<COM::RigidBody>(enemy, { sf::Vector2f(0,0), 250.0f, 100.0f });
    gCoordinator.AddComponent<COM::Sprite>(enemy, { sprite });
    gCoordinator.AddComponent<COM::Hitbox>(enemy, { 
        sf::Vector2f(64.0f, 64.0f),
        sf::Vector2f(43.0f, 60.0f),
        sf::Vector2f(0,0), 
        rect , 
        check_hitb });
    gCoordinator.GetComponent<COM::Hitbox>(enemy).initHitbox();
    gCoordinator.GetComponent<COM::Sprite>(enemy).sprite.setColor(sf::Color(0xff, 0x88, 0x88, 0xff));
    gCoordinator.AddComponent<COM::States>(enemy, {});
    gCoordinator.AddComponent<COM::Anim>(enemy, { nullptr, nullptr, 0.1f });

    //Animation load
    anim_manager.load_animation("idle", sf::Vector2f(43, 60), 0, 6);
    anim_manager.load_animation("idlef", sf::Vector2f(43, 60), 0, 6, 1);
    anim_manager.load_animation("run", sf::Vector2f(43, 60), 1, 6);
    anim_manager.load_animation("runf", sf::Vector2f(43, 60), 1, 6, 1);
    anim_manager.load_animation("jump", sf::Vector2f(43, 60), 2, 4);
    anim_manager.load_animation("jumpf", sf::Vector2f(43, 60), 2, 4, 1);
    anim_manager.load_animation("fall", sf::Vector2f(43, 60), 3, 4);
    anim_manager.load_animation("fallf", sf::Vector2f(43, 60), 3, 4, 1);
    anim_manager.load_animation("clim", sf::Vector2f(43, 60), 4, 6);
    anim_manager.load_animation("climf", sf::Vector2f(43, 60), 4, 6, 1);
    anim_manager.load_animation("roll", sf::Vector2f(43, 60), 5, 7);
    anim_manager.load_animation("rollf", sf::Vector2f(43, 60), 5, 7, 1);

    anim.init(0.1f);

    //player create
    player.SetView(&game_view);
    player.SetTexture(texture);
    player.SetAnimation(anim);
    player.SetAnimMgr(&anim_manager);
    player.Init(sf::Vector2f(32 * 15, 32 * 16));

    cur_ent = player.getEntity(); // for debug


    //parallax setup
    parallax_layer bg_sky;
    bg_sky.width = level.getMapSize().x * 2;
    bg_sky.parallax = 0.2f;
    bg_sky.texture = ResourceManager::getTexture("bg_sky");
    bg_sky.position = sf::Vector2f(-level.getMapSize().x * 0.5f,level.getMapSize().y * 0.5f);

    parallax_layer bg_clouds;
    bg_clouds.width = level.getMapSize().x * 2;
    bg_clouds.parallax = 0.5f;
    bg_clouds.texture = ResourceManager::getTexture("bg_clouds");
    bg_clouds.position = sf::Vector2f(-level.getMapSize().x * 0.5f,level.getMapSize().y * 0.5f);

    parallax_layer bg_sea;
    bg_sea.width = level.getMapSize().x * 2;
    bg_sea.parallax = 0.2f;
    bg_sea.texture = ResourceManager::getTexture("bg_sea");
    bg_sea.position = sf::Vector2f(-level.getMapSize().x * 0.5f,level.getMapSize().y * 0.5f);

    parallax_layer bg_ground;
    bg_ground.parallax = 0.5f;
    bg_ground.texture = ResourceManager::getTexture("bg_far-grounds");
    bg_ground.position = sf::Vector2f(level.getMapSize().x * 0.1f,level.getMapSize().y * 0.5f);

    back_ground.add_layer(bg_sky, true, false);
    back_ground.add_layer(bg_clouds, true, false);
    back_ground.add_layer(bg_sea, true, true);
    back_ground.add_layer(bg_ground, false, true);

}

void SceneThree::processInput()
{
    sf::Vector2f mousePos = this->engine->window.mapPixelToCoords(sf::Mouse::getPosition(this->engine->window), *this->view);
    mouse_p = mousePos;

    while (this->engine->window.pollEvent(*event))
    {
        ImGui::SFML::ProcessEvent(*event);

        switch (event->type)
        {
        case sf::Event::Closed:
        {
            engine->window.close();
            break;
        }
        case sf::Event::Resized:
        {
            this->view->setSize(event->size.width, event->size.height);
            this->game_view.setSize(event->size.width, event->size.height);
            this->hud_view.setSize(event->size.width, event->size.height);
            sf::Vector2f pos = sf::Vector2f(event->size.width, event->size.height);
            pos *= 0.5f;
            this->view->setCenter(pos);
            this->game_view.setCenter(pos);
            this->hud_view.setCenter(pos);
            pos = this->engine->window.mapPixelToCoords(sf::Vector2i(pos), *this->view);

            break;
        }
        case sf::Event::KeyPressed:
        {
            if (event->key.code == sf::Keyboard::Escape)
            {
                this->engine->_pop();
                return;
            }
            break;
        }
        case sf::Event::KeyReleased:
        {
            if ((event->key.code == sf::Keyboard::Tilde))
            {
                this->engine->_debug_ = !this->engine->_debug_;
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            if (event->mouseButton.button == sf::Mouse::Left)
            {

            }
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (event->mouseButton.button == sf::Mouse::Left)
            {

            }
            break;
        }
        case sf::Event::MouseMoved:
        {
            break;
        }
        default: break;
        }
    }
    // out poll event loop

}

void SceneThree::update(const float dt)
{
    //ECS update
    inputSystem->input(dt);
    physicsSystem->update(dt);
    cameraSystem->update();

    player.update(dt);

    ImGui::SFML::Update(this->engine->window, this->engine->clock.restart());

    view_pos = sf::Vector2f(game_view.getCenter().x, game_view.getCenter().y);

    updateUi(dt);
}

void SceneThree::render(const float dt)
{
    //mapdraw
    this->engine->window.setView(this->game_view);
    this->engine->window.clear(sf::Color(161,242,236,255));

    //parallax BG
    back_ground.setTarget(gCoordinator.GetComponent<COM::Transform>(player.getEntity()).position);
    this->engine->window.draw(back_ground);

    this->engine->window.setView(this->game_view);
    for (auto i : sprite_bg)
    {
        this->engine->window.draw(i);
    }

    this->engine->window.draw(level);

    //render scene obj
    renderSystem->draw(this->engine->window);

    //render gui
    this->engine->window.setView(this->hud_view);
    this->engine->window.draw(mtocell1);
    this->engine->window.draw(mtocell2);
    this->engine->window.draw(mtocell3);
    this->engine->window.draw(mtocell4);
    //debug
    if (_debugui_)
    {
        sfd::drawGrid(this->engine->window, 16, 9, sf::Color(0xff, 0x88, 0x88, 0xff));
    }


    this->engine->window.setView(game_view);
    if (_debugtile_) {
        sfd::drawGrid(this->engine->window, level.getTileSize(), sf::View(sf::FloatRect(-5000, -5000, 10000, 10000)), sf::Color(0xff, 0xff, 0xff, 0xff));
    }

    ImGui::SFML::Render(this->engine->window);

    return;
}

void SceneThree::cleanup()
{
}

void SceneThree::updateUi(const float dt)
{
    //imgui creation

    if (this->engine->_debug_)
    {
        ImGui::Begin("controll panel");
        ImGui::Checkbox("Dear Imgui", &check_im);
        ImGui::Checkbox("info win", &check_inf);
        ImGui::Checkbox("Tolltip", &check_ttp);
        ImGui::Checkbox("Ui grid", &_debugui_);
        ImGui::Checkbox("Tile grid", &_debugtile_);
        ImGui::Checkbox("COM test", &check_comt);
        ImGui::Checkbox("ECS test", &check_ecs);
        if (ImGui::Checkbox("Hitbox view", &check_hitb))
        {
            gCoordinator.GetComponent<COM::Hitbox>(player.getEntity()).draw = check_hitb;
            gCoordinator.GetComponent<COM::Hitbox>(enemy).draw = check_hitb;
        }

        if (ImGui::Button("Change entity"))
        {
            eop = !eop;
            if (eop)
            {
                cur_ent = enemy;
                gCoordinator.AddComponent<COM::View>(cur_ent, { &game_view });
                gCoordinator.AddComponent<COM::Input>(cur_ent, { std::vector<sf::Keyboard::Key>{sf::Keyboard::W,sf::Keyboard::A,sf::Keyboard::S,sf::Keyboard::D} });

                cur_ent = player.getEntity();

                gCoordinator.RemoveComponent<COM::View>(cur_ent);
                gCoordinator.RemoveComponent<COM::Input>(cur_ent);

                cur_ent = enemy;
            }
            else
            {
                cur_ent = player.getEntity();
                gCoordinator.AddComponent<COM::View>(cur_ent, { &game_view });
                gCoordinator.AddComponent<COM::Input>(cur_ent, { std::vector<sf::Keyboard::Key>{sf::Keyboard::W,sf::Keyboard::A,sf::Keyboard::S,sf::Keyboard::D} });

                cur_ent = enemy;
                gCoordinator.RemoveComponent<COM::View>(cur_ent);
                gCoordinator.RemoveComponent<COM::Input>(cur_ent);
                cur_ent = player.getEntity();
            }
        }ImGui::SameLine();
        ImGui::LabelText("Enemy control:", "%d", eop);

        ImGui::End();
    }

    if (check_inf)
    {
        ImGui::Begin("info win");
        ImGui::Text("mouse pos: (%g, %g)", mouse_p.x, mouse_p.y);
        ImGui::Text("world mouse pos: (%g, %g)",
            mouse_p.x + int(game_view.getCenter().x) - game_view.getSize().x * 0.5f,
            mouse_p.y + int(game_view.getCenter().y) - game_view.getSize().y * 0.5f);
        ImGui::Text("view pos: (%g, %g)", view_pos.x, view_pos.y);
        ImGui::End();
    }

    if (check_ttp)
    {
        ImGui::BeginTooltip();
        ImGui::Text("%d x %d",
            int((mouse_p.x + view_pos.x - game_view.getSize().x * 0.5f) / 32),
            int((mouse_p.y + view_pos.y - game_view.getSize().y * 0.5f) / 32));
        ImGui::EndTooltip();
    }

    if (check_im)
        ImGui::ShowDemoWindow();

    if (check_comt)
    {
        ImGui::Begin("com test");
        if (ImGui::CollapsingHeader("COM RigidBody"))
        {
            ImGui::Text("COM RigidBody:  \n  x = %g \n  y = %g \n  ACCELERATION = %g \n  MAX SPEED = %g ",
                gCoordinator.GetComponent<COM::RigidBody>(cur_ent).velocity.x,
                gCoordinator.GetComponent<COM::RigidBody>(cur_ent).velocity.y,
                gCoordinator.GetComponent<COM::RigidBody>(cur_ent)._ACCELERATION,
                gCoordinator.GetComponent<COM::RigidBody>(cur_ent)._MAXSPEED);
        }
        if (ImGui::CollapsingHeader("COM Transform"))
        {
            ImGui::Text("COM Transform.position:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Transform>(cur_ent).position.x,
                gCoordinator.GetComponent<COM::Transform>(cur_ent).position.y);
        }

        if (ImGui::CollapsingHeader("COM View"))
        {
            ImGui::Text("COM View:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::View>(cur_ent).view->getCenter().x,
                gCoordinator.GetComponent<COM::View>(cur_ent).view->getCenter().y);
        }

        if (ImGui::CollapsingHeader("COM Hitbox"))
        {
            ImGui::Text("COM Hitbox position:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).shape.getPosition().x,
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).shape.getPosition().y);

            ImGui::Text("COM Hitbox size:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).shape.getSize().x,
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).shape.getSize().y);

            ImGui::Text("COM Hitbox origin:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).shape.getOrigin().x,
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).shape.getOrigin().y);

            ImGui::Spacing();

            ImGui::Text("COM Hitbox param.position:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).position.x,
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).position.y);
            ImGui::Text("COM Hitbox param.size:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).size.x,
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).size.y);
            ImGui::Text("COM Hitbox param.center:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).center.x,
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).center.y);
            ImGui::Text("COM Hitbox param.offset:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).offset.x,
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).offset.y);

            ImGui::Text("COM Hitbox param.half:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).half.x,
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).half.y);

            ImGui::Text("COM Hitbox param.TL:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).TL.x,
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).TL.y);
            ImGui::Text("COM Hitbox param.ML:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).ML.x,
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).ML.y);
            ImGui::Text("COM Hitbox param.BL:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).BL.x,
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).BL.y);
            ImGui::Text("COM Hitbox param.TR:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).TR.x,
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).TR.y);
            ImGui::Text("COM Hitbox param.MR:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).MR.x,
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).MR.y);
            ImGui::Text("COM Hitbox param.BR:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).BR.x,
                gCoordinator.GetComponent<COM::Hitbox>(cur_ent).BR.y);
        }
        if (ImGui::CollapsingHeader("COM States"))
        {
            for (auto& [com, val] : gCoordinator.GetComponent<COM::States>(cur_ent).states)
            {
                std::string name = "  COM States." + com + ": %d";
                ImGui::Text(name.c_str(), val);
                ImGui::SameLine();
                if (ImGui::Button(com.c_str()))
                {
                    val = !val;
                }
            }
        }
        ImGui::End();
    }

    if (check_ecs)
    {
        ImGui::Begin("ecs test");
        if (ImGui::CollapsingHeader("Available Entity:"))
        {
            ImGui::Text("Entitys:  \n%d / %d",
                gCoordinator.getLivingEntity(), ECS::MAX_ENTITIES);
        }
        if (ImGui::CollapsingHeader("Physics:"))
        {
            ImGui::Text("Tile X at point: %d", level.getMapTileXAtPoint(gCoordinator.GetComponent<COM::Hitbox>(cur_ent).BL.x));
            ImGui::Text("Tile Y at point: %d", level.getMapTileYAtPoint(gCoordinator.GetComponent<COM::Hitbox>(cur_ent).BL.y));
        }
        ImGui::End();
    }
}
