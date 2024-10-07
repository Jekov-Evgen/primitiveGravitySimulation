#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>

const float GRAVITY = 0.001f;
const float GROUND_Y = 350.0f;

struct FallingCircle {
    sf::CircleShape shape;
    float velocityY;
};

bool isColliding(const sf::CircleShape& obj1, const sf::CircleShape& obj2) {
    return obj1.getGlobalBounds().intersects(obj2.getGlobalBounds());
}

void createFig(std::vector<FallingCircle>& circles, float radius) {
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Black);
    int x = rand() % 300;
    circle.setPosition(x, 0);

    FallingCircle fallingCircle = { circle, 0.0f };
    circles.push_back(fallingCircle);
}

int main()
{
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(400, 400), "Gravity");
    std::vector<FallingCircle> circles;
    bool drawCircle = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                drawCircle = true;
            }
        }

        if (drawCircle) {
            createFig(circles, 10);
            drawCircle = false;

            FallingCircle& newCircle = circles.back();
            for (size_t i = 0; i < circles.size() - 1; ++i) {
                if (isColliding(newCircle.shape, circles[i].shape)) {
                    circles.pop_back(); 
                    break;
                }
            }
        }

        for (auto& fallingCircle : circles) {
            fallingCircle.velocityY += GRAVITY;
            fallingCircle.shape.move(0, fallingCircle.velocityY);

            if (fallingCircle.shape.getPosition().y + fallingCircle.shape.getRadius() * 2 >= GROUND_Y) {
                fallingCircle.shape.setPosition(fallingCircle.shape.getPosition().x, GROUND_Y - fallingCircle.shape.getRadius() * 2);
                fallingCircle.velocityY = 0;
            }
        }

        window.clear(sf::Color::White);

        for (const auto& fallingCircle : circles) {
            window.draw(fallingCircle.shape);
        }

        if (circles.size() > 10) {
            circles.clear();
        }

        window.display();
    }

    return 0;
}