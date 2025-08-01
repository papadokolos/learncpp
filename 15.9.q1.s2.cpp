#include <iostream>

// Forward declaration
class Vector3d;

class Point3d
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point3d(double x, double y, double z)
        : m_x{x}, m_y{y}, m_z{z}
    { }

    void print() const
    {
        std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ")\n";
    }

    void moveByVector(const Vector3d& v);
};

class Vector3d
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Vector3d(double x, double y, double z)
        : m_x{x}, m_y{y}, m_z{z}
    {
    }

    void print() const
    {
        std::cout << "Vector(" << m_x << ", " << m_y << ", " << m_z << ")\n";
    }

    // Friend declaration requires full definition of Point3d
    friend void Point3d::moveByVector(const Vector3d& v);
};

void Point3d::moveByVector(const Vector3d& v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;
}

int main()
{
    Point3d p { 1.0, 2.0, 3.0 };
    Vector3d v { 2.0, 2.0, -3.0 };

    p.print();
    p.moveByVector(v);
    p.print();

    return 0;
}