#include "SceneManager.h"

void SceneManager::changeScene(Scene* scene)
{
    while (!scenes.empty()) {
        scenes.back()->cleanup();
        scenes.pop_back();
    }

    scenes.push_back(scene);
    scenes.back()->init();
}

void SceneManager::removeScene()
{
    while (!scenes.empty()) {
        scenes.back()->cleanup();
        scenes.pop_back();
    }

    if (!scenes.empty()) {
        scenes.back()->resume();
    }
}

void SceneManager::addScene(Scene* scene)
{
    while (!scenes.empty()) {
        scenes.back()->pause();
    }

    scenes.push_back(scene);
    scenes.back()->init();
}

void SceneManager::cleanup()
{
    while (!scenes.empty()) {
        scenes.back()->cleanup();
        scenes.pop_back();
    }
}

Scene SceneManager::getScene()
{
    return scenes.back();
}
