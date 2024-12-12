#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#pragma once

struct AboutContainer {
	bool isCreated = false;

	sf::Text fpsText;
	sf::Text devs;

	sf::Text devsList[4] = { sf::Text(), sf::Text(), sf::Text(), sf::Text() };
	std::wstring devNames[4] = {
		L"������ ����� ���������",
		L"���������� ����� ���������",
		L"��������� ����� �������",
		L"������ ������ ���������", 
	};

	sf::Text exit;
	sf::Font font;
	
	sf::SoundBuffer meowSoundBuff;
	sf::Sound meowSound;
};

AboutContainer* GetContainer();