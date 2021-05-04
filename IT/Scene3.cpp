#include <iostream>
#include "ResourceManager.h"
#include "Scene3.h"

SceneThree::SceneThree(Engine* engine)
{
    init(engine);
}

void SceneThree::init(Engine* engine)
{
    //core setup
    //res 1366 x 768 -> half 683 x 384 -> quad imposiible
    this->engine = engine;
    this->event = &engine->events;
    this->view = &engine->view;
    this->game_view = sf::View(sf::FloatRect(0, 0, 683, 384));
    this->hud_view = sf::View(sf::FloatRect(0, 0, 1366, 768));

    //view setup
    sf::Vector2f pos = sf::Vector2f(this->engine->window.getSize());
    this->view->setSize(pos);
    pos *= 0.5f;
    this->view->setCenter(pos);

    position = sf::Vector2f(0,0);

    texture.loadFromFile("../res/img/icon.png");
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setOrigin(32 * 0.5f, 32 * 0.5f);

    texture_bg.loadFromFile("../res/img/map.png");
    size_bg = sf::Vector2f(32, 32);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            sf::Sprite sprite;
            sprite.setTexture(texture_bg);
            sprite.setTextureRect(sf::IntRect(
                1 + (1 + size_bg.x) * j,
                1 + (1 + size_bg.y) * i,
                size_bg.x,
                size_bg.y));
            sprite.setPosition(size_bg.x * j, size_bg.y * i);

            sprite_bg.push_back(sprite);
        }
    }
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
            sf::Vector2f pos = sf::Vector2f(event->size.width, event->size.height);
            pos *= 0.5f;
            this->view->setCenter(pos);
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
            if (event->key.code == sf::Keyboard::W) { position.y -= 8; }
            if (event->key.code == sf::Keyboard::A) { position.x -= 8; }
            if (event->key.code == sf::Keyboard::S) { position.y += 8; }
            if (event->key.code == sf::Keyboard::D) { position.x += 8; }

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

void SceneThree::update(const float dt)
{
    ImGui::SFML::Update(this->engine->window, this->engine->clock.restart());


    game_view.setCenter(sprite.getPosition());
    sprite.setPosition(position);

    //imgui creation
    ImGui::Begin("info win");
    ImGui::Text("pos: (%g, %g)", mouse_p.x, mouse_p.y);
    ImGui::End();

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

    //render scene obj
    this->engine->window.draw(sprite);


    //render gui
    this->engine->window.setView(this->hud_view);



    ImGui::SFML::Render(this->engine->window);

    return;
}

void SceneThree::cleanup()
{
}

