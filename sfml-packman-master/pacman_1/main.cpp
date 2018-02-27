#include <SFML/Graphics.hpp>

// -- объявления констант --
constexpr unsigned ANTIALIASING_LEVEL = 8;
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned MAX_FPS = 60;

// -- предварительные объявления функций (всех, кроме main) --
void createWindow(sf::RenderWindow &window);
void initializePackman(sf::CircleShape &shape);
void handleEvents(sf::RenderWindow &window);
void update(sf::Clock &clock, sf::CircleShape &shape);
void render(sf::RenderWindow &window, sf::CircleShape &shape);

// -- определения функций --

// Функция создаёт окно приложения.
void createWindow(sf::RenderWindow &window)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    window.create(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "PacMan Game Clone", sf::Style::Default, settings);
    window.setFramerateLimit(MAX_FPS);
}

// Функция инициализирует фигуру пакмана.
void initializePackman(sf::CircleShape &shape, sf::CircleShape &eye, sf::ConvexShape &mouth)
{
    shape.setRadius(20);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(100, 0);

    eye.setRadius(3);
    eye.setFillColor(sf::Color::Black);
    eye.setPosition(125, 7);

    mouth.setPointCount(3);
    mouth.setPosition(120, 20);
    mouth.setPoint(0, sf::Vector2f(0, 0));
    mouth.setPoint(1, sf::Vector2f(20, -10));
    mouth.setPoint(2, sf::Vector2f(20, 10));
    mouth.setFillColor(sf::Color::Black);
}

// Функция обрабатывает все события, скопившиеся в очереди событий SFML.
void handleEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

// Функция обновляет фигуру пакмана.
void update(sf::Clock &clock, sf::CircleShape &shape, sf::CircleShape &eye, sf::ConvexShape &mouth)
{
    const sf::Vector2f speed = {10, 0};

    const float elapsedSeconds = clock.restart().asSeconds();
    shape.setPosition(shape.getPosition() + speed * elapsedSeconds);
    eye.setPosition(eye.getPosition() + speed * elapsedSeconds);
    mouth.setPosition(mouth.getPosition() + speed * elapsedSeconds);
}

// Функция рисует фигуру пакмана.
void render(sf::RenderWindow &window, sf::CircleShape &shape, sf::CircleShape &eye, sf::ConvexShape &mouth)
{
    window.clear();
    window.draw(shape);
    window.draw(eye);
    window.draw(mouth);
    window.display();
}

int main(int, char *[])
{
    sf::RenderWindow window;
    createWindow(window);

    sf::CircleShape packman;
    sf::CircleShape eye;
    sf::ConvexShape mouth;

    initializePackman(packman, eye, mouth);

    sf::Clock clock;
    while (window.isOpen())
    {
        handleEvents(window);
        update(clock, packman, eye, mouth);
        render(window, packman, eye, mouth);
    }

    return 0;
}
