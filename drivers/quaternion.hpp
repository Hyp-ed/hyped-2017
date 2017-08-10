#ifndef QUATERNION_HPP_
#define QUATERNION_HPP_

#include "vector3d.hpp"

class Quaternion
{
  public:
    double scal;
    Vector3D<double> vect;

    Quaternion();
    Quaternion(Vector3D<double> vector_part);
    Quaternion(double scalar_part, Vector3D<double> vector_part);
    Quaternion(double a, double b, double c, double d);

    Quaternion& operator+=(const Quaternion &rhs);
    Quaternion& operator-=(const Quaternion &rhs);
    Quaternion& operator*=(const Quaternion &rhs);
    Quaternion& operator*=(const double rhs);
    Quaternion& operator/=(const double rhs);

    operator Vector3D<double>() const;

    Quaternion operator-() const;

    static double norm(const Quaternion& q);
    static Quaternion conjugate(const Quaternion& q);
    static Quaternion inv(const Quaternion& q);
    static Quaternion pow(const Quaternion base, double exponent);
};

Quaternion operator+(Quaternion lhs, const Quaternion &rhs);
Quaternion operator-(Quaternion lhs, const Quaternion& rhs);
Quaternion operator*(Quaternion lhs, const Quaternion& rhs);
Quaternion operator*(Quaternion lhs, const double rhs);
Quaternion operator*(const double lhs, Quaternion rhs);
Quaternion operator/(Quaternion lhs, const double rhs);

#endif // QUATERNION_HPP_

