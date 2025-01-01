#include "HeaderFC.h"
#include "other/keyboard/KeyboardHeader.h"

#include "other/mouse/MouseHeader.h"
#include "frames/menu/MenuHeader.h"
#include "frames/game/GameHeader.h"
#include "frames/gameMenu/GameMenuHeader.h"
#include "frames/about/AboutHeader.h"

// ���������� ���� ��� �������� ������ ����
void UpdateFrames(std::string frameName) {
	for (auto &gettedFrame : GetFrames()) {
		if (gettedFrame.first == frameName) { continue; }
		if (!gettedFrame.second->IsEnabled()) { continue; }

		gettedFrame.second->Close();
		break;
	}
}

// ������� ���� ����� ���
void OpenFrame(std::string frameName) {
	GetFrames()[frameName]->Open();
}

// ������� ������� ����
void Render(sf::RenderWindow &window, int fps) {
	std::string openedFrame = GetOpenedFrame();

	UpdateKeyboard(window, openedFrame);
	UpdateMouse(window, openedFrame);
	GetFrames()[openedFrame]->Render(window, fps);
};

// �������� �������� �� ������ ������ ����
std::string GetOpenedFrame() {
	for (auto& gettedFrame : GetFrames()) {
		if ((gettedFrame.second->IsEnabled())) { return gettedFrame.second->frameName; }
	}

	return GetFrames()["menu"]->frameName;
}

struct FramesStorage {
	bool init = false;
	std::map <std::string, Frame*> frames;
};

struct FramesStorage storage;
// ��������� ���� ���� ����������
std::map <std::string, Frame*> GetFrames() {
	if (!storage.init) {
		storage.init = true;
		storage.frames["gameMenu"] = GetGameMenu();
		storage.frames["game"] = GetGame();
		storage.frames["menu"] = GetMenu();
		storage.frames["about"] = GetAbout();
	}

	return storage.frames;
}