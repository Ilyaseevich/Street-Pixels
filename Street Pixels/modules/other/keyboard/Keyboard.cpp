#include "KeyboardHeader.h"
_storageOfKeyboardFunctions storageFunctions;

// �������� �������
void UpdateKeyboard(sf::RenderWindow &window, std::string openedFrame) {
	for (_keyboardInfo &kInfo : storageFunctions) {
		if (!std::get<1>(kInfo) && (KeyPressed(std::get<0>(kInfo))) && (window.hasFocus())) {
			std::get<1>(kInfo) = true;
		}
		else {
			if ((!KeyPressed(std::get<0>(kInfo)) || (!window.hasFocus())) && (std::get<1>(kInfo))) {
				std::get<1>(kInfo) = false;
			}
			continue;
		}

		for (std::tuple<std::string, keyboardFunc> &frameInfo : std::get<2>(kInfo)) {
			if (std::get<0>(frameInfo).compare(openedFrame) != 0) { continue; }
			std::get<1>(frameInfo)(window);
		}
	}
}

// ������� �� ������ ����������(����������� �������)
int KeyPressConnect(sf::Keyboard::Key key, std::string frameName, keyboardFunc function) {
	_keyboardInfo* keyboardKey = GetKeyboardKey(key);

	std::get<2>(*keyboardKey).push_back(std::tuple<std::string, keyboardFunc>(frameName, function));
	return std::get<2>(*keyboardKey).size() - 1;
}

// ������� �� ������ ����������(���������� �������)
void KeyPressDisconnect(sf::Keyboard::Key key, int id) {
	if (!keyBoardExist(key)) { return; }
	_keyboardInfo keyboardKey = *GetKeyboardKey(key);
	std::get<2>(keyboardKey).erase( std::next(std::get<2>(keyboardKey).begin(), id) );
}

// �������� _keyboardInfo �������
_keyboardInfo* GetKeyboardKey(sf::Keyboard::Key key) {
	for (_keyboardInfo &kInfo : storageFunctions) {
		if (std::get<0>(kInfo) == key) { return &kInfo; }
	}

	storageFunctions.push_back({key, false, std::vector<std::tuple<std::string, keyboardFunc>>()});
	return &storageFunctions[storageFunctions.size() - 1];
}

// ������ �� ������
bool KeyPressed(sf::Keyboard::Key key) {
	return sf::Keyboard::isKeyPressed(key);
}

// ���������� �� _keyboardInfo �������
bool keyBoardExist(sf::Keyboard::Key key) {
	for (_keyboardInfo &kInfo : storageFunctions) {
		if (std::get<0>(kInfo) == key) { return true; }
	}

	return false;
}