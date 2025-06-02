#include <string>
#include <string_view>
#include <print>


class Ball
{
public:
    Ball(double radius);
    Ball(
        std::string_view color  = default_color,
        double radius           = default_radius);

    const std::string& getColor() const { return m_color; }
    double getRadius() const { return m_radius; }

private:
    // Note static data members are inline
    // (to be able to define inside class definition (within a header file))
    static inline const std::string_view default_color { "black" };
    static inline const double default_radius { 10.0 };

    std::string m_color { default_color };
    double m_radius { default_radius };
};

void print(const Ball& ball);

Ball::Ball(double radius) : Ball(default_color, radius) {}

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