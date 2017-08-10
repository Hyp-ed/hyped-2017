#include "quaternion.hpp"

#include <cmath>

Quaternion::Quaternion() : scal(0), vect(0, 0, 0)
{}

Quaternion::Quaternion(Vector3D<double> vector_part)
    : scal(0.0), vect(vector_part)
{}

Quaternion::Quaternion(double scalar_part, Vector3D<double> vector_part)
    : scal { scalar_part }, vect { vector_part }
{}

Quaternion::Quaternion(double a, double b, double c, double d)
    : scal(a), vect(b, c, d)
{}

Quaternion& Quaternion::operator+=(const Quaternion &rhs)
{
  this->scal += rhs.scal;
  this->vect += rhs.vect;
  return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion &rhs)
{
  *this += -rhs;
  return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion &rhs)
{
  double a = this->scal * rhs.scal - this->vect.x * rhs.vect.x
         - this->vect.y * rhs.vect.y - this->vect.z * rhs.vect.z;
  double b = this->scal * rhs.vect.x + this->vect.x * rhs.scal
            + this->vect.y * rhs.vect.z - this->vect.z * rhs.vect.y;
  double c = this->scal * rhs.vect.y + this->vect.y * rhs.scal
            - this->vect.x * rhs.vect.z + this->vect.z * rhs.vect.x;
  double d = this->scal * rhs.vect.z + this->vect.z * rhs.scal
            + this->vect.x * rhs.vect.y - this->vect.y * rhs.vect.x;
  this->scal = a;
  this->vect.x = b;
  this->vect.y = c;
  this->vect.z = d;
  return *this;
}

Quaternion& Quaternion::operator*=(const double rhs)
{
  this->scal *= rhs;
  this->vect *= rhs;
  return *this;
}

Quaternion& Quaternion::operator/=(const double rhs)
{
  this->scal /= rhs;
  this->vect /= rhs;
  return *this;
}

Quaternion::operator Vector3D<double>() const
{
  return this->vect;
}

Quaternion Quaternion::operator-() const
{
  return Quaternion(-this->scal, -this->vect);
}

Quaternion Quaternion::pow(double exp) const
{
  double theta = acos(this->scal / Quaternion::norm(*this));
  return pow(Quaternion::norm(*this), exp) * Quaternion(cos(exp * theta),
      sin(exp * theta) * this->vect / Quaternion::norm(this->vect));
}

double Quaternion::norm(const Quaternion& q)
{
  return sqrt(q.scal * q.scal + q.vect.x * q.vect.x
      + q.vect.y * q.vect.y + q.vect.z * q.vect.z);
}

Quaternion Quaternion::conjugate(const Quaternion& q)
{
  return Quaternion(q.scal, -q.vect);
}

Quaternion Quaternion::inv(const Quaternion& q)
{
  return Quaternion::conjugate(q)
      / (q.scal * q.scal + q.vect.x * q.vect.x
      + q.vect.y * q.vect.y + q.vect.z * q.vect.z);
}

Quaternion operator+(Quaternion lhs, const Quaternion &rhs)
{
  lhs += rhs;
  return lhs;
}

Quaternion operator-(Quaternion lhs, const Quaternion& rhs)
{
  lhs -= rhs;
  return lhs;
}

Quaternion operator*(Quaternion lhs, const Quaternion& rhs)
{
  lhs *= rhs;
  return lhs;
}

Quaternion operator*(Quaternion lhs, const double rhs)
{
  lhs *= rhs;
  return lhs;
}

Quaternion operator*(const double lhs, Quaternion rhs)
{
  rhs *= lhs;
  return rhs;
}

Quaternion operator/(Quaternion lhs, const double rhs)
{
  lhs /= rhs;
  return lhs;
}

