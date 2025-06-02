#include <string>
#include <string_view>
#include <print>


class Ball
{
public:
    Ball();
    Ball(std::string_view color);
    Ball(double radius);
    Ball(std::string_view color, double radius);

    const std::string& getColor() const { return m_color; }
    double getRadius() const { return m_radius; }

private:
    std::string m_color { "black" };
    double m_radius { 10.0 };
};

void print(const Ball& ball);

Ball::Ball()
{
    print(*this);
}

Ball::Ball(std::string_view color)
    : m_color { color }
{
    print(*this);
}

Ball::Ball(double radius)
    : m_radius { radius }
{
    print(*this);
}

Ball::Ball(std::string_view color, double radius)
    : m_color { color }, m_radius { radius }
{
    print(*this);
}

void print(const Ball& ball)
{
    std::println("Ball({}, {})", ball.getColor(), ball.getRadius());
}


int main()
{
    Ball def{};
    Ball blue{ "blue" };
    Ball twenty{ 20.0 };
    Ball blueTwenty{ "blue", 20.0 };

    return 0;
}