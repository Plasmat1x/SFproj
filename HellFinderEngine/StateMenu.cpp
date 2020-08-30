#include "StateMenu.h"

StateMenu StateMenu::m_StateMenu;

void StateMenu::Init(System* game)
{
    buttons.push_back(Start);
    buttons.push_back(Options);
    buttons.push_back(Exit);

	view.reset(sf::FloatRect(0,0,game->GetWindowSize().x, game->GetWindowSize().y));
	Start.Init("res/img/button.png", "", sf::Vector2f((game->GetWindowSize().x / 2), 38*6), sf::IntRect(0, 0, 120, 37), 2, game);
	if (game->isGame == false) {
		Start.SetText("Start");
	}
	else {
		Start.SetText("Continue");
	}

	Options.Init("res/img/button.png","Options", sf::Vector2f((game->GetWindowSize().x / 2), 38 * 8), sf::IntRect(0, 0, 120, 37), 2, game);
	Exit.Init("res/img/button.png", "Exit", sf::Vector2f((game->GetWindowSize().x / 2), 38*10), sf::IntRect(0, 0, 120, 37), 2, game);
}

void StateMenu::Cleanup()
{

}

void StateMenu::Pause()
{

}

void StateMenu::Resume()
{

}

void StateMenu::HandleEvents(System* game)
{
	if (Start.signal) {
		if (game->isGame == false) {
			game->PushState(StateGame::Instance());
		}
		else {
			game->PopState();
		}
	}
	if (Exit.signal) { game->GetWindow().close(); }
	if (Options.signal) { game->PushState(StateOptions::Instance()); }
}

void StateMenu::Update(System* game, float Time)
{
    for (int iter = 0; iter < buttons.size(); iter++)
    {
        buttons[iter].Update(Time, game);
        if (buttons[iter].AABB(game->getCursorPosition()) && ((game->GetEvent().type == sf::Event::MouseButtonPressed) && (game->GetEvent().key.code == sf::Mouse::Left)))
        {
            buttons[iter].action();
        }
        else
        {
            buttons[iter].endAction();
        }

        if (iter == buttons.size())
        {
            iter = 0;
        }
    }
}

void StateMenu::Render(System* game)
{
	game->GetWindow().setView(view);
	game->GetWindow().clear(sf::Color(70, 70, 120));
	Start.Render(game);
	Options.Render(game);
	Exit.Render(game);
	game->GetWindow().display();
}


//----------------------------------------------------------------------------------------------------------------------------------------

StateOptions StateOptions::m_StateOptions;

void StateOptions::Init(System* game)
{	
    buttons.push_back(Save);
    buttons.push_back(Return);

	Save.Init("res/img/button.png", "Save", sf::Vector2f(60 * 2, game->GetWindowSize().y - 18 * 2), sf::IntRect(0, 0, 120, 37), 2, game);
	Return.Init("res/img/button.png", "Return", sf::Vector2f(game->GetWindowSize().x - 60*2, game->GetWindowSize().y - 18*2), sf::IntRect(0, 0, 120, 37), 2, game);
}

void StateOptions::Cleanup()
{
}

void StateOptions::Pause()
{
}

void StateOptions::Resume()
{

}

void StateOptions::HandleEvents(System* game)
{
	if (Save.signal) { game->PopState(); }
}

void StateOptions::Update(System* game, float Time)
{

    for (int iter = 0; iter < buttons.size(); iter++)
    {
        buttons[iter].Update(Time, game);
        if (buttons[iter].AABB(game->getCursorPosition()) && ((game->GetEvent().type == sf::Event::MouseButtonPressed) && (game->GetEvent().key.code == sf::Mouse::Left)))
        {
            buttons[iter].action();
        }
        else
        {
            buttons[iter].endAction();
        }

        if (iter == buttons.size())
        {
            iter = 0;
        }
    }
}

void StateOptions::Render(System* game)
{
	game->GetWindow().clear(sf::Color(70, 70, 120));
	Save.Render(game);
	Return.Render(game);
	game->GetWindow().display();
}

