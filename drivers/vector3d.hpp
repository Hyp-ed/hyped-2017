#ifndef VECTOR3D_H_
#define VECTOR3D_H_

template<typename T>
class Vector3D
{
  public:
  T x, y, z;

    Vector3D<T>(T x = 0, T y = 0, T z = 0)
    {
      this->x = x;
      this->y = y;
      this->z = z;
    }

  Vector3D<T> operator-() const;

  Vector3D<T> &operator+=(const Vector3D<T> &rhs);
  Vector3D<T> &operator+=(const T rhs);

  Vector3D<T> &operator-=(const Vector3D<T> &rhs);
  Vector3D<T> &operator-=(const T rhs);

  Vector3D<T> &operator*=(const T rhs); //scalar multiplication

  Vector3D<T> &operator/=(const T rhs); // scalar division
};

template<typename T>
Vector3D<T> Vector3D<T>::operator-() const
{
  return Vector3D<T>(-x, -y, -z);
}

template<typename T>
Vector3D<T> &Vector3D<T>::operator+=(const Vector3D<T> &rhs)
{
  this->x += rhs.x;
  this->y += rhs.y;
  this->z += rhs.z;
  return *this;
}

template<typename T>
Vector3D<T> &Vector3D<T>::operator+=(const T rhs)
{
  this->x += rhs;
  this->y += rhs;
  this->z += rhs;
  return *this;
}

template<typename T>
Vector3D<T> &Vector3D<T>::operator-=(const Vector3D<T> &rhs)
{
  *this += -rhs;
  return *this;
}

template<typename T>
Vector3D<T> &Vector3D<T>::operator-=(const T rhs)
{
  *this += -rhs;
  return *this;
}

template<typename T>
Vector3D<T> &Vector3D<T>::operator*=(const T rhs)
{
  this->x *= rhs;
  this->y *= rhs;
  this->z *= rhs;
  return *this;
}

template<typename T>
Vector3D<T> &Vector3D<T>::operator/=(const T rhs)
{
  this->x /= rhs;
  this->y /= rhs;
  this->z /= rhs;
  return *this;
}


template<typename T>
Vector3D<T> operator+(Vector3D<T> lhs, const Vector3D<T> &rhs)
{
  lhs += rhs;
  return lhs;
}

template<typename T>
Vector3D<T> operator+(Vector3D<T> lhs, const T rhs)
{
  lhs += rhs;
  return lhs;
}

template<typename T>
Vector3D<T> operator+(const T lhs, Vector3D<T> rhs)
{
  rhs += lhs;
  return rhs;
}

template<typename T>
Vector3D<T> operator-(Vector3D<T> lhs, const Vector3D<T> &rhs)
{
  lhs -= rhs;
  return lhs;
}

template<typename T>
Vector3D<T> operator-(Vector3D<T> lhs, const T rhs)
{
  lhs -= rhs;
  return lhs;
}

template<typename T>
Vector3D<T> operator-(const T lhs, Vector3D<T> rhs)
{
  return (-rhs) += lhs;
}

template<typename T>
Vector3D<T> operator*(Vector3D<T> lhs, const T rhs)
{
  lhs *= rhs;
  return lhs;
}

template<typename T>
Vector3D<T> operator*(const T lhs, Vector3D<T> rhs)
{
  rhs *= lhs;
  return rhs;
}

template<typename T>
Vector3D<T> operator/(Vector3D<T> lhs, const T rhs)
{
  lhs /= rhs;
  return lhs;
}

/*template<typename T>
std::ostream &operator<<(std::ostream &out, const Vector3D<T> &v)
{
  out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return out;
}//*/

#endif  // VECTOR3D_H_