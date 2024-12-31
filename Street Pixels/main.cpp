#include <SFML/Graphics.hpp>
#include "modules/HeaderFC.h"

int main() {
    // �������� ���� ����
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Street Pixel", sf::Style::Fullscreen);
    OpenFrame("menu");

    //��������� �������
    sf::Cursor cursor; sf::Image cursorImage; 
    cursorImage.loadFromFile("imgs/cursor.png"); 
    cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 50));
    window.setMouseCursor(cursor);

    // �������� FPS
    window.setFramerateLimit(144);
    sf::Clock fpsClock;
    int fps = 144;
    
    //���������� ������ ����������
    sf::Image icon;
    if (!icon.loadFromFile("imgs/icon.png")){
        return 1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    


    // ������
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        Render(window, fps);
        window.display();

        fps = 1000 / fpsClock.getElapsedTime().asMilliseconds();
        fpsClock.restart();
    }

    return 0;
}


