#ifndef VECTOR_H
#define VECTOR_H

#include <ostream>

class Vector
{
public:
    double x;
    double y;

    Vector(double x = 0, double y = 0);
    Vector(const Vector& v);
    Vector& operator = (Vector const& v);
    Vector operator + (Vector const& v);
    Vector operator - (Vector const& v);
    Vector operator * (double scalar);
    double operator * (Vector const & v);

    Vector& operator += (Vector const& v);
    Vector& operator -= (Vector const& v);
    Vector& operator *= (double scalar);
};

std::ostream& operator<<(std::ostream& os, const Vector& v);

#endif // VECTOR_H
