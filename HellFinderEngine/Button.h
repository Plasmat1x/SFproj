#include"System.h"

class Button {
public:
    enum btState {
        IDLE,
        PRESSED,
        RELEASED
    };

    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Text text;
    sf::Font font;

    sf::Vector2f position;
    sf::IntRect size;
    float scale;
    sf::String sText;

    bool focus = false;
    bool signal = false;
    btState curState;
    btState prevState;

	void Init(std::string Path,sf::String stext, sf::Vector2f Position, sf::IntRect Size, int s,  System *game);
	
	void Render(System *game);
	void Update(float time, System *game);

	void SetText(sf::String text);
	void SetSize(int Size);
	void SetTexture(std::string Path);
	void SetPosition(sf::Vector2f pos);
	void SetFont(std::string path);
	void SetColor(sf::Color color);

    bool AABB(sf::Vector2i pos);
    void changeState(btState state);
    void action();
    void endAction();

};
