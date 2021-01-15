#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>
#include <QDebug>

namespace mats
{

template <typename T> inline bool almostEqual(T v0, T v1, T epsilon = 0.0001)
{
    return std::abs(v0 - v1) < epsilon;
}

template <typename T> inline T sqr(const T &v) {return v * v;}

template<typename T> class Vector3
{
public:
    //! Ctor of class Vector3 using default
    Vector3() = default;

    //! Custom Ctor of class Vector3
    /*! Defines coordinates of Vector
        \param x    -   typedef xCoord
        \param y    -   typedef yCoord
        \param z    -   typedef zCoord
    */
    Vector3(T x, T y, T z = 0) : m_v{x, y, z}{}

    bool almostEqual(const Vector3 &v, T epsilon = 0.0001) const
    {
        return (almostEqual(v.x(), m_v[0]) and
                almostEqual(v.y(), m_v[1]) and
                almostEqual(v.z(), m_v[2]));
    }

    T x() const
    {
        return m_v[0];
    }

    T &x()
    {
        return m_v[0];
    }

    T y() const
    {
        return m_v[1];
    }

    T &y()
    {
        return m_v[1];
    }

    T z() const
    {
        return m_v[2];
    }

    T &z()
    {
        return m_v[2];
    }

    Vector3 normalized() const
    {
        Vector3 v(*this);

        v.normalize();

        return v;
    }

    T normalize()
    {
        T   l = length();

        *this /= l;

        return l;
    }

    T lengthSquared() const
    {
        return (sqr(m_v[0]) + sqr(m_v[1]) + sqr(m_v[2]));
    }

    T length() const
    {
        return std::sqrt(lengthSquared());
    }

    Vector3 perp2D() const {return {-m_v[1], m_v[0], 0.0};}

    Vector3 invert() const {return {-m_v[0], -m_v[1], -m_v[2]};}

/* ++++++++++++++++++++++++++++++++OPERATORS+++++++++++++++++++++++++++++++ */
    const T &operator[](int i) const {return m_v[i];}
    T       &operator[](int i) {return m_v[i];}

    Vector3 operator * (const T &multiplier) const
    {
        return Vector3(m_v[0] * multiplier, m_v[1] * multiplier, m_v[2] * multiplier);
    }

    T operator * (const Vector3 &other)
    {
        return m_v[0] * other.x() + m_v[1] * other.y() + m_v[2] * other.z();
    }

    Vector3 operator ^ (const Vector3 &other) const
    {
        T m_x = m_v[1] * other.z() - m_v[2] * other.y();
        T m_y = m_v[2] * other.x() - m_v[0] * other.z();
        T m_z = m_v[0] * other.y() - m_v[1] * other.x();

        return Vector3(m_x, m_y, m_z);
    }

    friend Vector3 operator * (T s, const Vector3 &me)
    {
        return me * s;
    }

    Vector3 &operator *= (const T &multiplier)
    {
        m_v[0] *= multiplier;
        m_v[1] *= multiplier;
        m_v[2] *= multiplier;

        return *this;
    }

    Vector3 operator / (const T &divisor) const
    {
        return {m_v[0] / divisor, m_v[1] / divisor, m_v[2] / divisor};
    }

    Vector3 operator /= (const T &divisor)
    {
        return Vector3((m_v[0] /= divisor), (m_v[1] /= divisor), (m_v[2] /= divisor));
    }

    Vector3 operator + (const Vector3 &other) const
    {
        return Vector3(m_v[0] + other.x(), m_v[1] + other.y(), m_v[2] + other.z());
    }

    friend Vector3 operator + (T value, const Vector3 &me)
    {
        return me + value;
    }

    Vector3 operator += (const Vector3 &other)
    {
        return Vector3((m_v[0] += other.x()), (m_v[1] += other.x()), (m_v[2] += other.x()));
    }

    Vector3 operator - (const Vector3 &other) const
    {
        return Vector3(m_v[0] - other.x(), m_v[1] - other.y(), m_v[2] - other.z());
    }

    friend Vector3 operator - (T value, Vector3 &me)
    {
        return me - value;
    }

    Vector3 operator -= (const Vector3 &other)
    {
        return Vector3((m_v[0] -= other.x()), (m_v[1] -= other.x()), (m_v[2] -= other.x()));
    }

    bool operator == (const Vector3 &other) const
    {
        if(m_v[0] == other.x() && m_v[1] == other.y() && m_v[2] == other.z()){
            return true;
        }
        return false;
    }

    bool operator != (const Vector3 &other) const
    {
        return  not (*this==other);
    }

    /*! Compares the coordinates of both vectors. If one value of the left argument is smaller then it returns true, if bigger false and if every value is the same also false.
        \param other  -   Vector3 object of comparison
        \return bool    -   if smaller, equal or bigger
    */
    bool operator < (const Vector3 &other) const
    {
        if(m_v[0] < other.x()){
            return true;
        }
        if (m_v[0] > other.x()){
            return false;
        }
        if(m_v[1] < other.y()){
            return true;
        }
        if (m_v[1] > other.y()){
            return false;
        }
        return (m_v[2] < other.z());
    }

    bool operator > (const Vector3 &other) const
    {
        if(m_v[0] > other.x()){
            return true;
        }
        if (m_v[0] < other.x()){
            return false;
        }
        if(m_v[1] > other.y()){
            return true;
        }
        if (m_v[1] < other.y()){
            return false;
        }
        return (m_v[2] > other.z());
    }


private:
    T m_v[3] = {0, 0, 0};

};

template <typename T> std::ostream &operator<<(std::ostream &str, const Vector3<T> &v)
{
    return str << v.x() << " " << v.y() << " " << v.z();
}

template <typename T> QDebug &operator<<(QDebug dbg, const Vector3<T> &v)
{
    return dbg << v[0] << v[1] << v[2];
}

} // namespace

#endif // VECTOR_H
