#include "rotationmatrix.h"

#include <cmath>

RotationMatrix::RotationMatrix(double angle)
{
    angle = angle / 180.0 * M_PI;
    double c = cos(angle);
    double s = sin(angle);

    r0.x = c;
    r0.y = -s;
    r1.x = s;
    r1.y = c;
}

void RotationMatrix::transform(Vector& v)
{
    double x = v * r0;
    double y = v * r1;
    v.x = x;
    v.y = y;
}
