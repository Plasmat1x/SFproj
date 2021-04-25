#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct MultiObjStyle
{
    std::vector<int> index;
};

class MultiTileObject : public sf::Drawable, public sf::Transformable
{
private:
    std::vector<sf::Sprite> sprites;
    sf::Vector2f position;
    sf::Vector2f scale;
    sf::Vector2f addscale;
    sf::Vector2i size;
    sf::Texture* texture;
    sf::Vector2i arr_size;
    sf::IntRect globalbounds;
    int count;
    float padding;

    sf::Vector2f origin;

    void shater();
    void buildDepends();
    void calcBounds();
public:

    MultiTileObject() {}
    /// <summary>
    /// 
    /// </summary>
    /// <param name="texture"> ptr</param>
    /// <param name="position"> i</param>
    /// <param name="scale"> f</param>
    /// <param name="addscale"> f</param>
    /// <param name="in_size"> f</param>
    /// <param name="arr_size"></param>
    MultiTileObject(sf::Texture* texture,
        sf::Vector2f position,
        sf::Vector2f scale,
        sf::Vector2f addscale,
        sf::Vector2i size,
        sf::Vector2i arr_size,
        float padding)
    {
        this->texture = texture;
        this->position = position;
        this->scale = scale;
        this->addscale = addscale;
        this->size = size;
        this->arr_size = arr_size;
        this->padding = padding;
        count = 0;

        this->origin = sf::Vector2f(0, 0);

        shater();
        buildDepends();
        calcBounds();
    }
    MultiTileObject(sf::Texture* texture, sf::Vector2i size, sf::Vector2i arr_size, float padding)
    {
        this->texture = texture;
        this->size = size;
        this->arr_size = arr_size;

        this->origin = sf::Vector2f(0, 0);
        this->position = sf::Vector2f(0, 0);
        this->scale = sf::Vector2f(1.0f, 1.0f);
        this->addscale = sf::Vector2f(1.0f, 1.0f);
        this->padding = padding;

        shater();
        buildDepends();

        calcBounds();
    }

    sf::Sprite* getSprite(int index);
    sf::Sprite* getSprite(sf::Vector2f mousePos);
    int getSpriteAt(sf::Vector2f mousePos);
    sf::IntRect getGloablBounds();
    sf::Vector2i get_in_size();
    sf::Vector2f getaddscale();

    void setPosition(sf::Vector2f position);
    void setCenter(sf::Vector2i center);
    void setOrigin(sf::Vector2f origin);
    void setScale(sf::Vector2f scale);
    void setAddscale(sf::Vector2f addscale);
    void setSize(sf::Vector2f size);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
   
};

