#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#pragma once
	
void UpdateFrames(std::string);
void OpenFrame(std::string);
void Render(sf::RenderWindow &window, int);

class Frame {
private:
	bool isEnabled = false;
public:
	std::string frameName = "frame";

	// ������� �����: ��������� ��� ����������, ���������� ���!
	void Open() {
		isEnabled = true;
		UpdateFrames(frameName);
	}
	
	// ������� �����, �������������� ����� �� ������������ ������ �����.
	void Close() {
		isEnabled = false;
	}

	// !!! ������� �������, ������� ���������� ��������� � ������ ��������� ������
	// �������������� !!!
	void (*Render)(sf::RenderWindow&, int fps);

	// ������ �� �����
	bool IsEnabled() {
		return isEnabled;
	}
};

std::map <std::string, Frame*> GetFrames();