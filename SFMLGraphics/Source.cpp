#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>

using namespace sf;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    RenderWindow window(sf::VideoMode(800, 600), "Анимация линии в SFML");
    SoundBuffer buffer;    
    buffer.loadFromFile("sound.ogg");// тут загружаем в буфер что то
    Sound sound;
    sound.setLoop(true); // Включаем зацикливание воспроизведения
    sound.setVolume(30); // Устанавливаем громкость на 30% от максимальной
    sound.setBuffer(buffer);
    sound.play();

    // Создаем линию, используя sf::VertexArray
    VertexArray line(sf::Lines, 2);

    // Исходные позиции точек линии
    Vector2f startPosition(100.f, 100.f);
    Vector2f endPosition(500.f, 300.f);
    line[0].position = startPosition;
    line[1].position = endPosition;

    // Устанавливаем цвета точек линии
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Blue;

    // Скорости движения точек линии
    float horizontalVelocity = 100.f; // Скорость движения начальной точки по горизонтали
    float verticalVelocity = 50.f;    // Скорость движения конечной точки по вертикали

    Clock clock; // Таймер для измерения прошедшего времени

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds(); // Получаем время, прошедшее с последнего кадра

        // Обновляем позиции точек линии
        startPosition.x += horizontalVelocity * deltaTime;
        endPosition.y += verticalVelocity * deltaTime;

        // Проверка на границы окна для начальной точки
        if (startPosition.x > 800.f || startPosition.x < 0.f) {
            horizontalVelocity = -horizontalVelocity; // Меняем направление движения
        }

        // Проверка на границы окна для конечной точки
        if (endPosition.y > 600.f || endPosition.y < 0.f) {
            verticalVelocity = -verticalVelocity; // Меняем направление движения
        }

        // Присваиваем новые позиции точкам в массиве
        line[0].position = startPosition;
        line[1].position = endPosition;

        window.clear();
        window.draw(line); // Рисуем линию
        window.display();
    }

    return 0;
}
