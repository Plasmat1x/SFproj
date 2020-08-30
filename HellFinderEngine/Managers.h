#include "System.h"
#include "Button.h"

class ButtonManager
{
public:
	void Init();
	void Create();
	void Add();
	void SetFont();
	void SetSize();
	void SetTexture();
	void LoadFont();
	void LoadTexture();
	void SetText();
private:

	sf::Text text;
	sf::Font font;
	int size;
	int scale;

	std::vector<Button> vButtons;
};