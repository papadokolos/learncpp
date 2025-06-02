#include <print>
#include <string>
#include <string_view>


class Ball
{
public:
    Ball(std::string_view color, double radius);
    
    constexpr const std::string& getColor() const { return m_color; }
    constexpr double getRadius() const { return m_radius; }

private:
    std::string m_color { "black" };
    double m_radius { 0 };
};

Ball::Ball(std::string_view color, double radius)
    : m_color { color }
    , m_radius { radius }
{}

void print(const Ball& ball)
{
    std::println("Ball({}, {})", ball.getColor(), ball.getRadius());
}

int main()
{
    Ball blue { "blue", 10.0 };
    print(blue);

    Ball red { "red", 12.0 };
    print(red);

    return 0;
}