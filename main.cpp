#include "Engine.h"

Engine* eng;

int main()
{
    eng = new Engine();

    delete eng;
    system("Pause");
    return EXIT_SUCCESS;
}