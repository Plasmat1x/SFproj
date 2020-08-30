#include "Engine.h"
#include "Scene.h"
#include "Scene1.h"
#include "Scene2.h"

Engine::Engine()
{
    isRunign = true;
    init();

    while (window.isOpen())
    {
        while (window.pollEvent(events))
        {
            if (events.type == sf::Event::Closed) { window.close(); }
            if ((keyboardInput(sf::Keyboard::LAlt) || keyboardInput(sf::Keyboard::RAlt)) && keyboardInput(sf::Keyboard::F4)) { window.close(); }
        }
        processInput();
        update();
        render();
    }
}

Engine::~Engine()
{
    cleanup();
}

void Engine::init()
{
    window.create(sf::VideoMode(800, 600), "one");
    addScene(SceneOne::instance());
}

void Engine::update()
{
    scenes.back()->update(this);
}

void Engine::processInput()
{
    scenes.back()->processInput(this);
}

void Engine::render()
{
    scenes.back()->render(this);

    window.display();
}

bool Engine::keyboardInput(sf::Keyboard::Key key)
{
    if (sf::Keyboard::isKeyPressed(key))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Engine::mouseInput(sf::Mouse::Button button)
{
    if (sf::Mouse::isButtonPressed(button))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Engine::changeScene(Scene* scene)
{
    while (!scenes.empty()) {
        scenes.back()->cleanup();
        scenes.pop_back();
    }

    scenes.push_back(scene);
    scenes.back()->init();
}

void Engine::removeScene()
{
    while (!scenes.empty()) {
        scenes.back()->cleanup();
        scenes.pop_back();
    }

    if (!scenes.empty()) {
        scenes.back()->resume();
    }
}

void Engine::addScene(Scene* scene)
{
    while (!scenes.empty()) {
        scenes.back()->pause();
    }

    scenes.push_back(scene);
    scenes.back()->init();
}

void Engine::cleanup()
{
    while (!scenes.empty()) {
        scenes.back()->cleanup();
        scenes.pop_back();
    }
}

void Engine::shutDown()
{
    if (isRunign)
    {
        isRunign = false;
        window.close();
    }
}

sf::Vector2i Engine::getMousePosition()
{
    return sf::Mouse::getPosition(window);
}

