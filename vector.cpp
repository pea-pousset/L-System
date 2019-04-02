#include "vector.h"
#include <iomanip>

Vector::Vector(double x, double y)
    : x(x), y(y)
{
}

Vector::Vector(const Vector& v)
{
    x = v.x;
    y = v.y;
}

Vector& Vector::operator = (Vector const& v)
{
    this->x = v.x;
    this->y = v.y;
    return *this;
}

Vector Vector::operator + (Vector const& v)
{
    Vector r(*this);
    r.x += v.x;
    r.y += v.y;
    return r;
}

Vector Vector::operator - (Vector const& v)
{
    Vector r(*this);
    r.x -= v.x;
    r.y -= v.y;
    return r;
}

Vector Vector::operator * (double scalar)
{
    Vector r(*this);
    r.x *= scalar;
    r.y *= scalar;
    return r;
}

Vector& Vector::operator += (Vector const& v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector& Vector::operator -= (Vector const& v)
{
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vector& Vector::operator *= (double scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

double Vector::operator * (Vector const& v)
{
    return this->x * v.x + this->y * v.y;
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os << "[" << std::fixed << std::setprecision(2) << v.x << ", ";
    os << std::fixed << std::setprecision(2) << v.y << "]";
    return os;
}
