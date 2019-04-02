#ifndef ROTATIONMATRIX_H
#define ROTATIONMATRIX_H

#include "vector.h"

class RotationMatrix
{
public:
    RotationMatrix(double angle);   // Angle in degrees
    void transform(Vector& v);      // Apply rotation to vector v

private:
    // [ r0.x r0.y]
    // [ r1.x r1.y]
    Vector r0;
    Vector r1;
};

#endif // ROTATIONMATRIX_H
