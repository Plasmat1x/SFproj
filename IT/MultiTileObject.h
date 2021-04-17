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
    sf::Vector2i position;
    sf::Vector2f scale;
    sf::Vector2f addscale;
    sf::Vector2i size;
    sf::Texture* texture;
    sf::Vector2i arr_size;
    sf::IntRect globalbounds;
    int count;

    void shater();
    void buildDepends();
public:

    MultiTileObject() {}
    MultiTileObject(sf::Texture* texture, sf::Vector2i size, sf::Vector2i arr_size) 
    {
        this->texture = texture;
        this->size = size;
        this->arr_size = arr_size;

        this->position = sf::Vector2i(0,0);
        this->scale = sf::Vector2f(1.0f, 1.0f);
        this->addscale = sf::Vector2f(1.0f, 1.0f);

        shater();
        buildDepends();

        int x = this->position.x;

        int y = this->position.y;

        int w = (this->sprites[0].getLocalBounds().width * this->scale.x) +
            (this->sprites[2].getLocalBounds().width * this->scale.x) +
            (this->sprites[1].getLocalBounds().width * (this->scale.x * addscale.x));

        int h = (this->sprites[0].getLocalBounds().height * this->scale.y) +
            (this->sprites[3].getLocalBounds().height * this->scale.y) +
            (this->sprites[6].getLocalBounds().height * (this->scale.y * addscale.y));

        this->globalbounds = sf::IntRect(x, y, w, h);
    }
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
        sf::Vector2i position,
        sf::Vector2f scale,
        sf::Vector2f addscale,
        sf::Vector2i size,
        sf::Vector2i arr_size)
    {
        this->texture = texture;
        this->position = position;
        this->scale = scale;
        this->addscale = addscale;
        this->size = size;
        this->arr_size = arr_size;
        count = 0;

        shater();
        buildDepends();

        int x = this->position.x;

        int y = this->position.y;

        int w = (this->sprites[0].getLocalBounds().width * this->scale.x) +
            (this->sprites[2].getLocalBounds().width * this->scale.x) +
            (this->sprites[1].getLocalBounds().width * (this->scale.x * addscale.x));

        int h = (this->sprites[0].getLocalBounds().height * this->scale.y) +
            (this->sprites[3].getLocalBounds().height * this->scale.y) +
            (this->sprites[6].getLocalBounds().height * (this->scale.y * addscale.y));

        this->globalbounds = sf::IntRect(x, y, w, h);
    }

    sf::Sprite* getSprite(int index);
    sf::IntRect getGloablBounds();

    void setPosition(sf::Vector2i position);
    void setCenter(sf::Vector2i center);
    void setOrigin(sf::Vector2i origin);
    void setScale(sf::Vector2f scale);
    void setAddscale(sf::Vector2f addscale);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
   
};

