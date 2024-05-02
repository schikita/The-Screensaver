#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>

using namespace sf;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    RenderWindow window(sf::VideoMode(800, 600), "�������� ����� � SFML");
    SoundBuffer buffer;    
    buffer.loadFromFile("sound.ogg");// ��� ��������� � ����� ��� ��
    Sound sound;
    sound.setLoop(true); // �������� ������������ ���������������
    sound.setVolume(30); // ������������� ��������� �� 30% �� ������������
    sound.setBuffer(buffer);
    sound.play();

    // ������� �����, ��������� sf::VertexArray
    VertexArray line(sf::Lines, 2);

    // �������� ������� ����� �����
    Vector2f startPosition(100.f, 100.f);
    Vector2f endPosition(500.f, 300.f);
    line[0].position = startPosition;
    line[1].position = endPosition;

    // ������������� ����� ����� �����
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Blue;

    // �������� �������� ����� �����
    float horizontalVelocity = 100.f; // �������� �������� ��������� ����� �� �����������
    float verticalVelocity = 50.f;    // �������� �������� �������� ����� �� ���������

    Clock clock; // ������ ��� ��������� ���������� �������

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds(); // �������� �����, ��������� � ���������� �����

        // ��������� ������� ����� �����
        startPosition.x += horizontalVelocity * deltaTime;
        endPosition.y += verticalVelocity * deltaTime;

        // �������� �� ������� ���� ��� ��������� �����
        if (startPosition.x > 800.f || startPosition.x < 0.f) {
            horizontalVelocity = -horizontalVelocity; // ������ ����������� ��������
        }

        // �������� �� ������� ���� ��� �������� �����
        if (endPosition.y > 600.f || endPosition.y < 0.f) {
            verticalVelocity = -verticalVelocity; // ������ ����������� ��������
        }

        // ����������� ����� ������� ������ � �������
        line[0].position = startPosition;
        line[1].position = endPosition;

        window.clear();
        window.draw(line); // ������ �����
        window.display();
    }

    return 0;
}
