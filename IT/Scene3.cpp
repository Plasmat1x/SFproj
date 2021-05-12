#include <iostream>
#include <cmath>
#include "ResourceManager.h"
#include "Scene3.h"
#include "dGrid.h"

#include "COM_LIB.h"
#include "SYS_LIB.h"

std::shared_ptr<SYS::PhysicsSystem> physicsSystem;
std::shared_ptr<SYS::RenderSystem> renderSystem;
std::shared_ptr<SYS::CameraSystem> cameraSystem;
std::shared_ptr<SYS::InputSystem> inputSystem;

static bool quit = false;


void QuitHandler(ECS::Event& event)
{
    quit = true;
}

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
    //this->game_view = sf::View(sf::FloatRect(0, 0, 683, 384));
    //this->game_view = sf::View(sf::FloatRect(0, 0, 1366, 768));
    //this->hud_view = sf::View(sf::FloatRect(0, 0, 1366, 768));
    this->game_view = engine->view;
    this->hud_view = engine->view;

    //view setup
    sf::Vector2f pos = sf::Vector2f(this->engine->window.getSize());
    this->view->setSize(pos);
    pos *= 0.5f;
    this->view->setCenter(pos);

    this->hud_view.setCenter(pos);

    texture.loadFromFile("../res/img/elf.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 43, 60));
    sprite.setOrigin(44 * 0.5f, 60 * 0.5f);

    texture_bg.loadFromFile("../res/img/map.png");

    level = Level("../res/map/test_level.tmx", &texture_bg, sf::Vector2i(2, 3));

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

    gCoordinator.AddEventListener(ECS::FUNCTION_LISTENER(Events::Window::QUIT, QuitHandler));

    gCoordinator.RegisterComponent<COM::c_position>();
    gCoordinator.RegisterComponent<COM::c_velocity>();
    gCoordinator.RegisterComponent<COM::c_sprite>();
    gCoordinator.RegisterComponent<COM::c_view>();
    gCoordinator.RegisterComponent<COM::c_input>();
    gCoordinator.RegisterComponent<COM::c_hitbox>();
    gCoordinator.RegisterComponent<COM::c_animation>();
    gCoordinator.RegisterComponent<COM::c_state>();

    //Physic
    physicsSystem = gCoordinator.RegisterSystem<SYS::PhysicsSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<COM::c_position>());
        signature.set(gCoordinator.GetComponentType<COM::c_velocity>());
        signature.set(gCoordinator.GetComponentType<COM::c_hitbox>());
        signature.set(gCoordinator.GetComponentType<COM::c_state>());
        gCoordinator.SetSystemSignature<SYS::PhysicsSystem>(signature);
    }

    //Render
    renderSystem = gCoordinator.RegisterSystem<SYS::RenderSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<COM::c_position>());
        signature.set(gCoordinator.GetComponentType<COM::c_sprite>());
        signature.set(gCoordinator.GetComponentType<COM::c_hitbox>());
        gCoordinator.SetSystemSignature<SYS::RenderSystem>(signature);
    }


    //View
    cameraSystem = gCoordinator.RegisterSystem<SYS::CameraSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<COM::c_position>());
        signature.set(gCoordinator.GetComponentType<COM::c_view>());
        gCoordinator.SetSystemSignature<SYS::CameraSystem>(signature);
    }

    //Control
    inputSystem = gCoordinator.RegisterSystem<SYS::InputSystem>();
    {
        ECS::Signature signature;
        signature.set(gCoordinator.GetComponentType<COM::c_input>());
        signature.set(gCoordinator.GetComponentType<COM::c_velocity>());
        signature.set(gCoordinator.GetComponentType<COM::c_state>());
        signature.set(gCoordinator.GetComponentType<COM::c_animation>());
        gCoordinator.SetSystemSignature<SYS::InputSystem>(signature);
    }inputSystem->init();

    sf::RectangleShape rect;
    rect.setFillColor(sf::Color(0xff, 0xff, 0xff, 0x00));
    rect.setOutlineColor(sf::Color(0xff, 0xff, 0x88, 0xff));
    rect.setOutlineThickness(1.0f);

    player = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<COM::c_position>(player, { 0.0f, 0.0f });
    gCoordinator.AddComponent<COM::c_velocity>(player, { 0.0f, 0.0f, 500.0f, 200.0f });
    gCoordinator.AddComponent<COM::c_sprite>(player, { sprite });
    gCoordinator.AddComponent<COM::c_input>(player, { std::vector<sf::Keyboard::Key>{sf::Keyboard::W,sf::Keyboard::A,sf::Keyboard::S,sf::Keyboard::D} });
    gCoordinator.AddComponent<COM::c_view>(player, { &game_view });
    gCoordinator.AddComponent<COM::c_hitbox>(player, { sf::Vector2f(43,60), sf::Vector2f(0.0f, 22.0f), rect , check_hitb });
    gCoordinator.GetComponent<COM::c_hitbox>(player).initHitbox();
    gCoordinator.AddComponent<COM::c_state>(player, {
        std::map<const char*, bool>{
        {"idle", true},
        {"run", false},
        {"jump", false},
        {"fall", false},
        {"clim", false} },

        std::map<const char*, bool>{
            {"onGround", true},
            {"direction", true} },
        });
    gCoordinator.AddComponent<COM::c_animation>(player, { &gCoordinator.GetComponent<COM::c_sprite>(player).sprite, Animation(0.03f), AnimationManager()});
    gCoordinator.GetComponent<COM::c_animation>(player).anim_mgr.load_animation("idle",     sf::Vector2f(43, 60), 0, 6);
    gCoordinator.GetComponent<COM::c_animation>(player).anim_mgr.load_animation("idlef",    sf::Vector2f(43, 60), 0, 6, 1);
    gCoordinator.GetComponent<COM::c_animation>(player).anim_mgr.load_animation("run",      sf::Vector2f(43, 60), 1, 6);
    gCoordinator.GetComponent<COM::c_animation>(player).anim_mgr.load_animation("runf",     sf::Vector2f(43, 60), 1, 6, 1);
    gCoordinator.GetComponent<COM::c_animation>(player).anim_mgr.load_animation("jump",     sf::Vector2f(43, 60), 2, 4);
    gCoordinator.GetComponent<COM::c_animation>(player).anim_mgr.load_animation("jumpf",    sf::Vector2f(43, 60), 2, 4, 1);
    gCoordinator.GetComponent<COM::c_animation>(player).anim_mgr.load_animation("fall",     sf::Vector2f(43, 60), 3, 4);
    gCoordinator.GetComponent<COM::c_animation>(player).anim_mgr.load_animation("fallf",    sf::Vector2f(43, 60), 3, 4, 1);
    gCoordinator.GetComponent<COM::c_animation>(player).anim_mgr.load_animation("clim",     sf::Vector2f(43, 60), 4, 6);
    gCoordinator.GetComponent<COM::c_animation>(player).anim_mgr.load_animation("climf",    sf::Vector2f(43, 60), 4, 6, 1);

    enemy = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<COM::c_position>(enemy, { 64.0f, 64.0f });
    gCoordinator.AddComponent<COM::c_velocity>(enemy, { 0.0f, 0.0f, 500.0f, 200.0f });
    gCoordinator.AddComponent<COM::c_sprite>(enemy, { sprite });
    gCoordinator.AddComponent<COM::c_hitbox>(enemy, { sf::Vector2f(43,60), sf::Vector2f(0.0f, 22.0f), rect , check_hitb });
    gCoordinator.GetComponent<COM::c_hitbox>(enemy).initHitbox();
    gCoordinator.GetComponent<COM::c_sprite>(enemy).sprite.setColor(sf::Color(0xff, 0x88, 0x88, 0xff));

    //anim.init(0.1f);
}

void SceneThree::processInput()
{
    sf::Vector2f mousePos = this->engine->window.mapPixelToCoords(sf::Mouse::getPosition(this->engine->window), *this->view);
    mouse_p = mousePos;


    //ImGui::SFML::ProcessEvent(*event);

    while (this->engine->window.pollEvent(*event))
    {
        ImGui::SFML::ProcessEvent(*event);
        bool buttonStateChanged = true;

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

            bool buttonStateChanged = true;
            if (event->key.code == sf::Keyboard::W)
            {
                mButtons.set(static_cast<size_t>(ECS::InputButtons::W));
            }
            else if (event->key.code == sf::Keyboard::A)
            {
                mButtons.set(static_cast<size_t>(ECS::InputButtons::A));
            }
            else if (event->key.code == sf::Keyboard::S)
            {
                mButtons.set(static_cast<size_t>(ECS::InputButtons::S));
            }
            else if (event->key.code == sf::Keyboard::D)
            {
                mButtons.set(static_cast<size_t>(ECS::InputButtons::D));
            }
            else if (event->key.code == sf::Keyboard::Q)
            {
                mButtons.set(static_cast<size_t>(ECS::InputButtons::Q));
            }
            else if (event->key.code == sf::Keyboard::E)
            {
                mButtons.set(static_cast<size_t>(ECS::InputButtons::E));
            }
            else
            {
                buttonStateChanged = false;
            }

            if (buttonStateChanged)
            {
                ECS::Event ev(ECS::Events::Window::INPUT);
                ev.SetParam(ECS::Events::Window::Input::INPUT, mButtons);
                gCoordinator.SendEvent(ev);
            }

            break;
        }
        case sf::Event::KeyReleased:
        {
            if ((event->key.code == sf::Keyboard::Tilde))
            {
                this->engine->_debug_ = !this->engine->_debug_;
            }

            bool buttonStateChanged = true;
            if (event->key.code == sf::Keyboard::W)
            {
                mButtons.reset(static_cast<size_t>(ECS::InputButtons::W));
            }
            else if (event->key.code == sf::Keyboard::A)
            {
                mButtons.reset(static_cast<size_t>(ECS::InputButtons::A));
            }
            else if (event->key.code == sf::Keyboard::S)
            {
                mButtons.reset(static_cast<size_t>(ECS::InputButtons::S));
            }
            else if (event->key.code == sf::Keyboard::D)
            {
                mButtons.reset(static_cast<size_t>(ECS::InputButtons::D));
            }
            else if (event->key.code == sf::Keyboard::Q)
            {
                mButtons.reset(static_cast<size_t>(ECS::InputButtons::Q));
            }
            else if (event->key.code == sf::Keyboard::E)
            {
                mButtons.reset(static_cast<size_t>(ECS::InputButtons::E));
            }
            else
            {
                buttonStateChanged = false;
            }

            if (buttonStateChanged)
            {
                ECS::Event ev(ECS::Events::Window::INPUT);
                ev.SetParam(ECS::Events::Window::Input::INPUT, mButtons);
                gCoordinator.SendEvent(ev);
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

    /*
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { anim.play(&gCoordinator.GetComponent<COM::c_sprite>(player).sprite, anim_manager.getAnimation("run")); }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { anim.play(&gCoordinator.GetComponent<COM::c_sprite>(player).sprite, anim_manager.getAnimation("runf")); }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { anim.play(&gCoordinator.GetComponent<COM::c_sprite>(player).sprite, anim_manager.getAnimation("runf")); }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { anim.play(&gCoordinator.GetComponent<COM::c_sprite>(player).sprite, anim_manager.getAnimation("run")); }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        anim.play(&gCoordinator.GetComponent<COM::c_sprite>(player).sprite, anim_manager.getAnimation("idle"));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { anim.play(&gCoordinator.GetComponent<COM::c_sprite>(player).sprite, anim_manager.getAnimation("idle")); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { anim.play(&gCoordinator.GetComponent<COM::c_sprite>(player).sprite, anim_manager.getAnimation("run")); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) { anim.play(&gCoordinator.GetComponent<COM::c_sprite>(player).sprite, anim_manager.getAnimation("jump")); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) { anim.play(&gCoordinator.GetComponent<COM::c_sprite>(player).sprite, anim_manager.getAnimation("fall")); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) { anim.play(&gCoordinator.GetComponent<COM::c_sprite>(player).sprite, anim_manager.getAnimation("clim")); }
    //*/
}

void SceneThree::update(const float dt)
{
    //ECS update
    inputSystem->update(dt);
    physicsSystem->update(dt, level);
    cameraSystem->update();

    ImGui::SFML::Update(this->engine->window, this->engine->clock.restart());

    view_pos = sf::Vector2f(game_view.getCenter().x, game_view.getCenter().y);

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
        if (ImGui::Checkbox("Hitbox view", &check_hitb)) 
        {
            gCoordinator.GetComponent<COM::c_hitbox>(player).draw = check_hitb;
            gCoordinator.GetComponent<COM::c_hitbox>(enemy).draw = check_hitb;
        }

        if(ImGui::Button("Change entity"))
        {
            eop = !eop;
            if (eop)
            {
                gCoordinator.AddComponent<COM::c_view>(enemy, { &game_view });
                gCoordinator.AddComponent<COM::c_input>(enemy, { std::vector<sf::Keyboard::Key>{sf::Keyboard::W,sf::Keyboard::A,sf::Keyboard::S,sf::Keyboard::D} });

                gCoordinator.RemoveComponent<COM::c_view>(player);
                gCoordinator.RemoveComponent<COM::c_input>(player);
            }
            else
            {
                gCoordinator.AddComponent<COM::c_view>(player, { &game_view });
                gCoordinator.AddComponent<COM::c_input>(player, { std::vector<sf::Keyboard::Key>{sf::Keyboard::W,sf::Keyboard::A,sf::Keyboard::S,sf::Keyboard::D} });

                gCoordinator.RemoveComponent<COM::c_view>(enemy);
                gCoordinator.RemoveComponent<COM::c_input>(enemy);
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
        if (ImGui::CollapsingHeader("COM velocity"))
        {
            ImGui::Text("COM Velocity:  \n  x = %g \n  y = %g \n  ACCELERATION = %g \n  MAX SPEED = %g ",
                gCoordinator.GetComponent<COM::c_velocity>(player).x,
                gCoordinator.GetComponent<COM::c_velocity>(player).y,
                gCoordinator.GetComponent<COM::c_velocity>(player)._ACCELERATION,
                gCoordinator.GetComponent<COM::c_velocity>(player)._MAXSPEED);
        }
        if (ImGui::CollapsingHeader("COM position"))
        {
            ImGui::Text("COM Position:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::c_position>(player).x,
                gCoordinator.GetComponent<COM::c_position>(player).y);
        }

        if (ImGui::CollapsingHeader("COM view"))
        {
            ImGui::Text("COM View:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::c_view>(player).view->getCenter().x,
                gCoordinator.GetComponent<COM::c_view>(player).view->getCenter().y);
        }

        if (ImGui::CollapsingHeader("COM hitbox"))
        {
            ImGui::Text("COM Hitbox position:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::c_hitbox>(player).shape.getPosition().x,
                gCoordinator.GetComponent<COM::c_hitbox>(player).shape.getPosition().y);

            ImGui::Text("COM Hitbox size:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::c_hitbox>(player).shape.getSize().x,
                gCoordinator.GetComponent<COM::c_hitbox>(player).shape.getSize().y);

            ImGui::Text("COM Hitbox origin:  \n  x = %g \n  y = %g",
                gCoordinator.GetComponent<COM::c_hitbox>(player).shape.getOrigin().x,
                gCoordinator.GetComponent<COM::c_hitbox>(player).shape.getOrigin().y);
        }
        ImGui::End();
    }
}

void SceneThree::render(const float dt)
{
    //mapdraw
    this->engine->window.setView(this->game_view);
    this->engine->window.clear(sf::Color::Cyan);

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
        sfd::drawGrid(this->engine->window, sf::Vector2f(32, 32), sf::View(sf::FloatRect(-5000, -5000, 10000, 10000)), sf::Color(0xff, 0xff, 0xff, 0xff));
    }

    ImGui::SFML::Render(this->engine->window);

    return;
}

void SceneThree::cleanup()
{
}

void SceneThree::updateUi(sf::Vector2f pos)
{
    
}
