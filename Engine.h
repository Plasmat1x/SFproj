#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <mutex>
#include <cstdlib>

class Scene;

class Engine
{
public:

    sf::Event events;
    sf::RenderWindow window;

    bool isRunign;

    std::vector<Scene*> scenes;

    Engine();
    ~Engine();

    void init();
    void cleanup();
    void shutDown();

    void update();
    void processInput();
    void render();

    void changeScene(Scene* scene);
    void removeScene();
    void addScene(Scene* scene);

    bool keyboardInput(sf::Keyboard::Key key);
    bool mouseInput(sf::Mouse::Button button);

    sf::Vector2i getMousePosition();
};

