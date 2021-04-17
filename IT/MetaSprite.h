#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace meta
{
    /// <summary>
    /// info structure of style metasprite
    /// </summary>
    struct ElementsInfo
    {
        sf::Vector2i meta_count_elements;
        sf::Vector2f meta_scale;
        sf::Vector2i meta_size;
        int count;

        ElementsInfo() {}
        ElementsInfo(sf::Vector2f scale, sf::Vector2i m_count)
        {
            this->meta_count_elements = m_count;
            this->meta_scale = scale;
            this->count = m_count.x * m_count.y;
        }
    };

    /// <summary>
    /// info structure with indexes tileset what be used for each elements of meta atlas
    /// </summary>
    struct AtlasSpriteInfo
    {
        std::vector<int> tile_indexes;

        AtlasSpriteInfo() {}
        AtlasSpriteInfo(std::vector<int> indexes)
        {
            this->tile_indexes = indexes;
        }
    };

    class Atlas
    {
    private:
        sf::Texture* texture;
        ElementsInfo* info;
        sf::Vector2f scale;
        sf::Vector2i size_tile_set;
        std::vector<AtlasSpriteInfo>* meta_sprites;
        std::vector<sf::Sprite> tile_set;
        
        void shater(sf::Texture* texture);
    public:
        int count;

        Atlas(ElementsInfo* info, sf::Texture* texture, sf::Vector2f scale, std::vector<AtlasSpriteInfo>* spriteInfo)
        {
            this->info = info;
            this->texture = texture;
            this->scale = scale;
            this->meta_sprites = spriteInfo;

            shater(this->texture);
        }
    };

    class Sprite :
        public sf::Drawable, public sf::Transformable
    {
    public:

        Sprite() {}

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
    };
}



