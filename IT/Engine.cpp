#include "Engine.h"
#include "Scene.h"
#include "Scene1.h"

#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

#include <sstream>

ECS::Coordinator gCoordinator;

void Engine::init(CORE_Config* config)
{
    this->config = config;
    if (this->config->full_screen)
    {
        window.create(sf::VideoMode(this->config->width,this->config->height), this->config->app_name, sf::Style::Fullscreen);
    }
    else
    {
        window.create(sf::VideoMode(this->config->width, this->config->height), this->config->app_name, sf::Style::Titlebar | sf::Style::Close);
    }

    window.setVerticalSyncEnabled(this->config->v_sync);
    window.setFramerateLimit(this->config->frame_limit);
    
    ImGui::SFML::Init(window);
}

void Engine::update(const float dt)
{
    _peek()->update(dt);
}

void Engine::processInput()
{
    _peek()->processInput();
}

void Engine::render(const float dt)
{
    this->window.clear(sf::Color::Black);
    
    _peek()->render(dt);

    this->window.display();
}

void Engine::_change(Scene* scene)
{
    if (!this->scenes.empty())
    {
        _pop();
    }
    _push(scene);

    return;
}

void Engine::_pop()
{
    delete this->scenes.top();
    this->scenes.pop();

    return;
}

void Engine::_push(Scene* scene)
{
    this->scenes.push(scene);

    return;
}

Scene* Engine::_peek()
{
    if (this->scenes.empty()) return nullptr;

    return this->scenes.top();
}

void Engine::cleanup()
{
    while (!this->scenes.empty())
    {
        this->scenes.top()->cleanup();
        _pop();
    }
}

void Engine::core()
{
    sf::Time time = sf::Time::Zero;
    sf::Time tick = sf::seconds(1.f / 60.f);

    while (window.isOpen())
    {
        time = clock.restart();
        float dt = tick.asSeconds();
        if (_peek() == nullptr) continue;

        while (time > tick)
        {
            processInput();
            update(dt);
            render(dt);
        }
        time += clock.restart();
    }
    ImGui::SFML::Shutdown();
}

sf::Vector2i Engine::getMousePosition()
{
    return sf::Mouse::getPosition(window);
}


