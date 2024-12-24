#include "MenuHeader.h"
#include "objsContainer/MC_Header.h"
#include "../../other/keyboard/KeyboardHeader.h"
#include "../../other/mouse/MouseHeader.h"

// ������ ����
void Menu_Render(sf::RenderWindow &window, int fps) {
	MenuContainer *container = GetContainer();

	// FPS
	container->fpsText.setString(std::to_string(fps));
	
	// �����������
	container->game.setOrigin(sf::Vector2f(container->game.getLocalBounds().width / 2, 0));

	for (int i = 0; i < 3; i++) {
		container->buttons[i].setFillColor(sf::Color::White);
		container->buttons[i].setOrigin(sf::Vector2f(container->buttons[i].getLocalBounds().width / 2, 0));
	}

	// ������
	container->buttons[container->choice].setFillColor(sf::Color::Red);
		
	// ������
	window.draw(container->fpsText);
	window.draw(container->game);

	for (int i = 0; i < 3; i++) {
		window.draw(container->buttons[i]);
	}
}

// ���� �����������
void Menu_Closing() {
	MenuContainer* container = GetContainer();
	//container->choice = 0;
}

void Menu_ChoiceAdd(sf::RenderWindow &window) {
	MenuContainer* container = GetContainer();
	container->choice = (container->choice - 1 == -1) ? 2 : container->choice - 1;
}

void Menu_ChoiceRemove(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();
	container->choice = (container->choice + 1 == 3) ? 0 : container->choice + 1;
}


// ��������� ������ Play
void Menu_PlayHover(sf::RenderWindow& window) {
	GetContainer()->choice = 0;
}

// ��������� ������ About
void Menu_AboutHover(sf::RenderWindow& window) {
	GetContainer()->choice = 1;
}

// ��������� ������ ������
void Menu_ExitHover(sf::RenderWindow& window) {
	GetContainer()->choice = 2;
}



// ������� �� ������ Play
void Menu_PlayClick(sf::RenderWindow& window) {
	
}

// ������� �� ������ About
void Menu_AboutClick(sf::RenderWindow& window) {
	OpenFrame("about");
}

// ������� �� ������ Exit
void Menu_ExitClick(sf::RenderWindow& window) {
	window.close();
}



void Menu_Enter(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();

	switch (container->choice) {
		case(0): {

			break;
		}
		case(1): {
			OpenFrame("about");
			break;
		}
		case(2): {
			window.close();
			break;
		}
	}
}

Frame _createdMenu;
Frame* GetMenu() {
	if (_createdMenu.frameName == "frame") {
		_createdMenu.frameName = "menu";

		_createdMenu.Render = Menu_Render;
		_createdMenu.Closing = Menu_Closing;

		KeyPressConnect(sf::Keyboard::W, "menu", Menu_ChoiceAdd);
		KeyPressConnect(sf::Keyboard::Up, "menu", Menu_ChoiceAdd);

		KeyPressConnect(sf::Keyboard::S, "menu", Menu_ChoiceRemove);
		KeyPressConnect(sf::Keyboard::Down, "menu", Menu_ChoiceRemove);

		KeyPressConnect(sf::Keyboard::Enter, "menu", Menu_Enter);

		ConnectMouseHoverFunc("menu", &(GetContainer()->buttons[0]), Menu_PlayHover);
		ConnectMouseClickFunc("menu", &(GetContainer()->buttons[0]), Menu_PlayClick);

		ConnectMouseHoverFunc("menu", &(GetContainer()->buttons[1]), Menu_AboutHover);
		ConnectMouseClickFunc("menu", &(GetContainer()->buttons[1]), Menu_AboutClick);

		ConnectMouseHoverFunc("menu", &(GetContainer()->buttons[2]), Menu_ExitHover);
		ConnectMouseClickFunc("menu", &(GetContainer()->buttons[2]), Menu_ExitClick);
	}

	return &_createdMenu;
}