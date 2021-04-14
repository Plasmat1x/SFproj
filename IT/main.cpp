#include "Engine.h"
#include "Scene1.h"
#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

int main()
{
    Engine game;

    //init
    game.init();

    //load scene
    game._push(new SceneOne(&game));

    //core
    game.core();

    //cleanup
    game.cleanup();

    system("Pause");
    return EXIT_SUCCESS;
}