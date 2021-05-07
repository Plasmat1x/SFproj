#include <iostream>
#include "ResourceManager.h"
#include "Scene3.h"
#include "dGrid.h"

#include "COM_LIB.h"
#include "SYS_LIB.h"

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

    texture.loadFromFile("../res/img/icon.png");
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setOrigin(32 * 0.5f, 32 * 0.5f);

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

    //���������� UI
    sf::Vector2f uipos = pos;
    mtocell1.setPosition(sf::Vector2f(uipos.x - 96, uipos.y * 1.9f));
    mtocell2.setPosition(sf::Vector2f(uipos.x - 32, uipos.y * 1.9f));
    mtocell3.setPosition(sf::Vector2f(uipos.x + 32, uipos.y * 1.9f));
    mtocell4.setPosition(sf::Vector2f(uipos.x + 96, uipos.y * 1.9f));


    //ECS
    gCoordinator.Init();

    gCoordinator.RegisterComponent<COM::Position>();
    gCoordinator.RegisterComponent<COM::Velocity>();
    gCoordinator.RegisterComponent<COM::Sprite>();
    gCoordinator.RegisterComponent<COM::View>();
    gCoordinator.RegisterComponent<COM::InputComponent>();

    physicsSystem = gCoordinator.RegisterSystem<SYS::PhysicsSystem>();
    renderSystem = gCoordinator.RegisterSystem<SYS::RenderSystem>();
    cameraSystem = gCoordinator.RegisterSystem<SYS::CameraSystem>();
    inputSystem = gCoordinator.RegisterSystem<SYS::InputSystem>();

    ECS::Signature signature;
    signature.set(gCoordinator.GetComponentType<COM::Position>());
    signature.set(gCoordinator.GetComponentType<COM::Velocity>());
    gCoordinator.SetSystemSignature<SYS::PhysicsSystem>(signature);

    signature = 0;
    signature.set(gCoordinator.GetComponentType<COM::Position>());
    signature.set(gCoordinator.GetComponentType<COM::Sprite>());
    gCoordinator.SetSystemSignature<SYS::RenderSystem>(signature);

    signature = 0;
    signature.set(gCoordinator.GetComponentType<COM::Position>());
    signature.set(gCoordinator.GetComponentType<COM::View>());
    gCoordinator.SetSystemSignature<SYS::CameraSystem>(signature);

    signature = 0;
    signature.set(gCoordinator.GetComponentType<COM::InputComponent>());
    signature.set(gCoordinator.GetComponentType<COM::Velocity>());
    gCoordinator.SetSystemSignature<SYS::InputSystem>(signature);

    player = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<COM::Position>(player, { 1.0f, 1.0f });
    gCoordinator.AddComponent<COM::Velocity>(player, { 0.0f, 0.0f, 100.0f });
    gCoordinator.AddComponent<COM::Sprite>(player, { sprite });
    gCoordinator.AddComponent<COM::InputComponent>(player, { std::vector<sf::Keyboard::Key>{sf::Keyboard::W,sf::Keyboard::A,sf::Keyboard::S,sf::Keyboard::D} });
    gCoordinator.AddComponent<COM::View>(player, { &game_view });

    enemy = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<COM::Position>(enemy, { 64.0f, 64.0f });
    gCoordinator.AddComponent<COM::Velocity>(enemy, { 0.0f, 0.0f, 100.0f });
    gCoordinator.AddComponent<COM::Sprite>(enemy, { sprite });
}

void SceneThree::processInput()
{
    sf::Vector2f mousePos = this->engine->window.mapPixelToCoords(sf::Mouse::getPosition(this->engine->window), *this->view);
    mouse_p = mousePos;


    //ImGui::SFML::ProcessEvent(*event);

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
            if ((event->type == sf::Event::KeyPressed) && (event->key.code == sf::Keyboard::Escape))
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

            if ((event->key.code == sf::Keyboard::Num1))
            {
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

        case sf::Event::MouseMoved:
        {
            break;
        }
        default: break;
        }
        }
        }
    }
}

void SceneThree::update(const float dt)
{
    //ECS update
    inputSystem->input(dt);
    physicsSystem->update(dt);
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

        if(ImGui::Button("Change entity"))
        {
            eop = !eop;
            if (eop)
            {
                gCoordinator.AddComponent<COM::View>(enemy, { &game_view });
                gCoordinator.AddComponent<COM::InputComponent>(enemy, { std::vector<sf::Keyboard::Key>{sf::Keyboard::W,sf::Keyboard::A,sf::Keyboard::S,sf::Keyboard::D} });

                gCoordinator.RemoveComponent<COM::View>(player);
                gCoordinator.RemoveComponent<COM::InputComponent>(player);
            }
            else
            {
                gCoordinator.AddComponent<COM::View>(player, { &game_view });
                gCoordinator.AddComponent<COM::InputComponent>(player, { std::vector<sf::Keyboard::Key>{sf::Keyboard::W,sf::Keyboard::A,sf::Keyboard::S,sf::Keyboard::D} });

                gCoordinator.RemoveComponent<COM::View>(enemy);
                gCoordinator.RemoveComponent<COM::InputComponent>(enemy);
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
            mouse_p.x + game_view.getCenter().x - game_view.getSize().x * 0.5f,
            mouse_p.y + game_view.getCenter().y - game_view.getSize().y * 0.5f);
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
