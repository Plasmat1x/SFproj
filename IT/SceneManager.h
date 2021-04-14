#pragma once
#include <vector>
#include "Scene.h"

class SceneManager
{
public:
    static bool running;
    static std::vector<Scene> scenes;

    static void changeScene(Scene* scene);
    static void removeScene();
    static void addScene(Scene* scene);
    static void cleanup();

    static Scene getScene();

private:
    SceneManager() { _instance = this; }

    SceneManager* _instance;
};

