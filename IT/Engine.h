#pragma once
#include <GL/glew.h>

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
#include <Windows.h>
#include <stack>

class Scene;

class Engine
{
public:

    sf::Event events;
    sf::RenderWindow window;
    sf::Clock clock;
    std::stack<Scene*> scenes;
    sf::View view;

    //core
    void init();
    void cleanup();
    void core();
    

    //core sub func
    void processInput();
    void update(const float dt);
    void render(const float dt);

    //scenes
    void _change(Scene* scene);
    void _pop();
    void _push(Scene* scene);
    Scene* _peek();

    //utils
    sf::Vector2i getMousePosition();
};

