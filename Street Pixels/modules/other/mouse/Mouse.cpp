#include "MouseHeader.h"
mouseConnectors _mouseInfo;

// ������ ����
void UpdateMouse(sf::RenderWindow& window, std::string frameName) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition() - window.getPosition();

	// ���� ���� � �������
	for (hoverInfo& info : std::get<1>(_mouseInfo)) {
		if (std::get<0>(info) != frameName) { continue; }

		sf::Text *textObject = std::get<2>(info);

		sf::Vector2f txtPosition = textObject->getPosition();
		sf::Vector2f txtMinPosition = txtPosition + sf::Vector2f(-textObject->getLocalBounds().width / 2, 
			textObject->getCharacterSize() / 2);
		sf::Vector2f txtMaxPosition = txtPosition + sf::Vector2f(textObject->getLocalBounds().width / 2, 
			textObject->getLocalBounds().height + textObject->getCharacterSize());

		if ((mousePosition.x >= txtMinPosition.x) && (mousePosition.x <= txtMaxPosition.x)
			&& (mousePosition.y >= txtMinPosition.y) && (mousePosition.y <= txtMaxPosition.y)) {
			if (!std::get<1>(info)) {
				std::get<1>(info) = true;
				std::get<3>(info)(window);
			}
		}
		else {
			std::get<1>(info) = false;
		}
	}

	// ����� ���� �� �������
	for (hoverInfo& info : std::get<3>(_mouseInfo)) {
		if (std::get<0>(info) != frameName) { continue; }

		sf::Text* textObject = std::get<2>(info);

		sf::Vector2f txtPosition = textObject->getPosition();
		sf::Vector2f txtMinPosition = txtPosition + sf::Vector2f(-textObject->getLocalBounds().width / 2,
			textObject->getCharacterSize() / 2);
		sf::Vector2f txtMaxPosition = txtPosition + sf::Vector2f(textObject->getLocalBounds().width / 2,
			textObject->getLocalBounds().height + textObject->getCharacterSize());

		if ((mousePosition.x >= txtMinPosition.x) && (mousePosition.x <= txtMaxPosition.x)
			&& (mousePosition.y >= txtMinPosition.y) && (mousePosition.y <= txtMaxPosition.y)) {
			std::get<1>(info) = true;
		}
		else {
			if (std::get<1>(info)) { std::get<3>(info)(window); }
			std::get<1>(info) = false;
		}
	}

	// ������� ������ �� �������
	for (clickInfo &info : std::get<5>(_mouseInfo)) {
		if ((std::get<0>(info) != frameName)) { continue; }
		if (LeftMousePressed() && !std::get<0>(_mouseInfo)) {
			sf::Text* textObject = std::get<1>(info);

			sf::Vector2f txtPosition = textObject->getPosition();
			sf::Vector2f txtMinPosition = txtPosition + sf::Vector2f(-textObject->getLocalBounds().width / 2,
				textObject->getCharacterSize() / 2);
			sf::Vector2f txtMaxPosition = txtPosition + sf::Vector2f(textObject->getLocalBounds().width / 2,
				textObject->getLocalBounds().height + textObject->getCharacterSize());

			if ((mousePosition.x >= txtMinPosition.x) && (mousePosition.x <= txtMaxPosition.x)
				&& (mousePosition.y >= txtMinPosition.y) && (mousePosition.y <= txtMaxPosition.y)) {
				std::get<2>(info)(window);
			}
		}
	}

	// ���������� ������� ����
	std::get<0>(_mouseInfo) = LeftMousePressed();
}

// ���������� �������, ����� ���� ������ � �������
int* ConnectMouseHoverFunc(std::string frameName, sf::Text *text, mouseFunc func) {
	std::get<1>(_mouseInfo).push_back(hoverInfo(frameName, false, text, func));

	int* newId = new int(std::get<1>(_mouseInfo).size() - 1);
	std::get<2>(_mouseInfo).push_back(newId);

	return std::get<2>(_mouseInfo).back();
}

// ��������� �������, ����� ���� ������ � �������
void DisconnectMouseHoverFunc(int *id) {
	std::get<1>(_mouseInfo).erase(std::next(std::get<1>(_mouseInfo).begin(), *id));
	
	for (int *connectorId : std::get<2>(_mouseInfo)) { 
		if (*connectorId < *id) continue;
		(*connectorId)--;
	}
}

// ���������� �������, ����� ���� ������� �� �������
int* ConnectMouseHoverLeaveFunc(std::string frameName, sf::Text* text, mouseFunc func) {
	std::get<3>(_mouseInfo).push_back(hoverInfo(frameName, false, text, func));

	int* newId = new int(std::get<3>(_mouseInfo).size() - 1);
	std::get<4>(_mouseInfo).push_back(newId);

	return std::get<4>(_mouseInfo).back();
}

// ��������� �������, ����� ���� ������ � �������
void DisconnectMouseHoverLeaveFunc(int* id) {
	std::get<3>(_mouseInfo).erase(std::next(std::get<3>(_mouseInfo).begin(), *id));

	for (int* connectorId : std::get<4>(_mouseInfo)) {
		if (*connectorId < *id) continue;
		(*connectorId)--;
	}
}

// ���������� �������, ����� ���������� ������� �� ������� ������
int* ConnectMouseClickFunc(std::string frameName, sf::Text *text, mouseFunc func) {
	std::get<5>(_mouseInfo).push_back(clickInfo(frameName, text, func));

	int* newId = new int(std::get<5>(_mouseInfo).size() - 1);
	std::get<6>(_mouseInfo).push_back(newId);

	return std::get<6>(_mouseInfo).back();
}
	
// ��������� �������, ����� ���������� ������� �� ������� ������
void DisconnectMouseClickFunc(int* id) {
	std::get<6>(_mouseInfo).erase(std::next(std::get<6>(_mouseInfo).begin(), *id));
	for (int *connectorId : std::get<6>(_mouseInfo)) {
		if (*connectorId < *id) continue;
		(*connectorId)--;
	}
}

// ������ �� ���
bool LeftMousePressed() {
	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

// ������ �� ���
bool RightMousePressed() {
	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
}

// ��������� ������� �����
sf::Vector2i GetMousePosition() {
	return sf::Mouse::getPosition();
}