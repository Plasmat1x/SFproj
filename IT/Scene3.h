#pragma once
#include <vector>

#include "Engine.h"
#include "Scene.h"
#include "Gui.h"
#include "MultiTileObject.h"

#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

#include "_GUI.h"

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
    char windowTitle[255] = "ImGui + SFML = <3";
    float color[3] = { 0.f, 0.f, 0.f };
    sf::Color bgColor;

    sf::View game_view;
    sf::View hud_view;

    sf::Sprite sprite;
    std::vector<sf::Sprite> sprite_bg;
    sf::Texture texture;

    sf::Texture texture_bg;

    sf::Vector2f position;

    sf::Vector2f size_bg;
};

