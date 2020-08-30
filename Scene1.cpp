#include "Scene1.h"
#include "Scene2.h"

SceneOne SceneOne::m_SceneOne;

Button* entity0;
Button* entity1;

void SceneOne::init()
{
    entity0 = new Button("button.png", sf::Vector2f(340, 250), sf::Vector2i(120, 37), sf::IntRect(120, 0, 120, 37), 1.0f);
    entity1 = new Button("button.png", sf::Vector2f(340, 300), sf::Vector2i(120, 37), sf::IntRect(120, 0, 120, 37), 1.0f);

    entity0->initText("MorrisRomanBlack.ttf", sf::Vector2f(15, 0), "Next scene", 22);
    entity1->initText("MorrisRomanBlack.ttf", sf::Vector2f(40, 0), "Exit", 22);
    
    objects.push_back(entity0);
    objects.push_back(entity1);
}

void SceneOne::cleanup()
{
    while (!objects.empty()) {
        objects.pop_back();
    }

    delete entity0;
    delete entity1;
}

void SceneOne::pause()
{
}

void SceneOne::resume()
{
}

void SceneOne::processInput(Engine* engine)
{
    for (auto* e : objects)
    {
        if (engine->mouseInput(sf::Mouse::Left) && e->AABB(engine->getMousePosition()))
        {
            e->action();
        }
        else
        {
            e->deaction();
        }
    }

    if (engine->keyboardInput(sf::Keyboard::Right))
    {
        engine->changeScene(SceneTwo::instance());
    }
}

void SceneOne::update(Engine* engine)
{

    for (auto* e : objects)
    {
        e->AABB(engine->getMousePosition());
        e->update();
    }

    if (entity0->signal)
    {
        engine->changeScene(SceneTwo::instance());
    }

}

void SceneOne::render(Engine* engine)
{
    engine->window.clear(sf::Color::Blue);

    for (auto* e : objects)
    {
        engine->window.draw(e->sprite);
        engine->window.draw(e->text);
    }
}
