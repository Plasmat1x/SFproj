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

#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

#include "ECS.h"

static ECS::Coordinator gCoordinator;

struct CORE_Config
{
    std::string app_name;
    unsigned int width;
    unsigned int height;
    bool v_sync;
    unsigned int frame_limit;
    bool full_screen;
};

class Scene;

class Engine
{
public:
    bool _debug_ = false;

    sf::Event events;
    sf::RenderWindow window;
    sf::Clock clock;
    std::stack<Scene*> scenes;
    sf::View view;

    CORE_Config* config;

    //core
    void init(CORE_Config* config);
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

