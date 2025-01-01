#include "GameHeader.h"
#include "objsContainer/GC_Header.h"
#include "../../other/keyboard/KeyboardHeader.h"
#include "../../other/mouse/MouseHeader.h"

//������ ����
void Game_Render(sf::RenderWindow &window, int fps) {
	GameContainer* container = GetContainer();

	// FPS
	float _fpsValue = (fps / 144.0 > 1.0) ? (1.0) : (fps / 144.0);
	container->fpsText.setFillColor(sf::Color(255 - (int)(_fpsValue * 255), 255 - (255 - (int)(_fpsValue * 255)), 0, 255));
	container->fpsText.setString(std::to_string(fps));

	// ������
	window.draw(container->fpsText);

	if (container->_gamePaused) {
		std::get<0>(container->exitFrame).setOrigin(
			sf::Vector2f(std::get<0>(container->exitFrame).getLocalBounds().width / 2,
			std::get<0>(container->exitFrame).getLocalBounds().height / 2
		));

		window.draw(std::get<0>(container->exitFrame));
	}
}

// ��������� ��������� ����
void Game_LoadSettingsToGame(int countOfBots, int maxSpeed) {
	GetContainer()->_countOfBots = countOfBots;
	GetContainer()->_maxSpeed = maxSpeed;
}

// ����� �� ����
void Game_Close() {
	GetContainer()->_gameStarted = false;
	GetContainer()->_gamePaused = false;
}



// ����� ����� Escape
void Game_EscapePressed(sf::RenderWindow& window) {
	GameContainer* container = GetContainer();
	container->_gamePaused = !container->_gamePaused;
}

// ����� ����� Enter
void Game_EnterPressed(sf::RenderWindow& window) {
	GameContainer* container = GetContainer();

	if (container->_gamePaused) {
		OpenFrame("menu");
	}
}



Frame _createdGame;
Frame* GetGame() {
	if (_createdGame.frameName == "frame") {
		_createdGame.frameName = "game";

		KeyPressConnect(sf::Keyboard::Escape, "game", Game_EscapePressed);
		KeyPressConnect(sf::Keyboard::Enter, "game", Game_EnterPressed);

		_createdGame.Render = Game_Render;
		_createdGame.Closing = Game_Close;
	}

	return &_createdGame;
}