#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <map>

struct AnimationPlaylist
{
    std::vector<sf::IntRect> frames;
};

class AnimationManager
{
public:
    void load_animation(std::string anim_name, sf::Vector2f size, int line, int frames, bool flipp = false);
    AnimationPlaylist getAnimation(std::string anim_name);

    const std::map<std::string, AnimationPlaylist>& getAnimMap();

private:
    std::map<std::string, AnimationPlaylist> animations;
};

class Animation
{
public:
    void init(float speed);
    void play(sf::Sprite* sprite, AnimationPlaylist animation);
    void reset();

private:
    float frame;
    float speed;
};

/*
* constructor scene or init 
    texture.loadFromFile("../res/img/anim_wip.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 400, 240));
    sprite.setPosition(0, 0);

    //--------------------------/name/-----------size---------------/line/frames/flipped----
    anim_manager.load_animation("run",      sf::Vector2f(400, 240),     1,  6);
    anim_manager.load_animation("runf",     sf::Vector2f(400, 240),     1,  6,  1);
    anim_manager.load_animation("idle",     sf::Vector2f(400, 240),     0,  6);
    anim_manager.load_animation("idlef",    sf::Vector2f(400, 240),     0,  6,  1);
    anim_manager.load_animation("jump",     sf::Vector2f(400, 240),     2,  4);
    anim_manager.load_animation("jumpf",    sf::Vector2f(400, 240),     2,  4,  1);
    anim_manager.load_animation("fall",     sf::Vector2f(400, 240),     3,  4);
    anim_manager.load_animation("fallf",    sf::Vector2f(400, 240),     3,  4,  1);
    anim_manager.load_animation("clim",     sf::Vector2f(400, 240),     4,  6);
    anim_manager.load_animation("climf",    sf::Vector2f(400, 240),     4,  6,  1);

    anim.init(0.25f);

*input func
     case sf::Event::KeyPressed:
        {
            if (event.key.code == sf::Keyboard::Num1)
            {
                anim.play(&sprite, anim_manager.getAnimation("idle"));
            }




//usage with coordinator in input
if (event.key.code == sf::Keyboard::Numpad0) anim.play(&gCoordinator.GetComponent<COM::Sprite>(player).sprite, anim_manager.getAnimation("idle"));
            if (event.key.code == sf::Keyboard::Numpad1) anim.play(&gCoordinator.GetComponent<COM::Sprite>(player).sprite, anim_manager.getAnimation("idlef"));
            if (event.key.code == sf::Keyboard::Numpad2) anim.play(&gCoordinator.GetComponent<COM::Sprite>(player).sprite, anim_manager.getAnimation("run"));
            if (event.key.code == sf::Keyboard::Numpad3) anim.play(&gCoordinator.GetComponent<COM::Sprite>(player).sprite, anim_manager.getAnimation("runf"));
            if (event.key.code == sf::Keyboard::Numpad4) anim.play(&gCoordinator.GetComponent<COM::Sprite>(player).sprite, anim_manager.getAnimation("jump"));
            if (event.key.code == sf::Keyboard::Numpad5) anim.play(&gCoordinator.GetComponent<COM::Sprite>(player).sprite, anim_manager.getAnimation("jumpf"));
            if (event.key.code == sf::Keyboard::Numpad6) anim.play(&gCoordinator.GetComponent<COM::Sprite>(player).sprite, anim_manager.getAnimation("fall"));
            if (event.key.code == sf::Keyboard::Numpad7) anim.play(&gCoordinator.GetComponent<COM::Sprite>(player).sprite, anim_manager.getAnimation("fallf"));
            if (event.key.code == sf::Keyboard::Numpad8) anim.play(&gCoordinator.GetComponent<COM::Sprite>(player).sprite, anim_manager.getAnimation("clim"));
            if (event.key.code == sf::Keyboard::Numpad9) anim.play(&gCoordinator.GetComponent<COM::Sprite>(player).sprite, anim_manager.getAnimation("climf"));
*/