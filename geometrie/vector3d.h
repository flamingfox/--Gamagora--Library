#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <iostream>
#include <cmath>


class Vector3D
{
public:

    float x,y,z;

    Vector3D();
    Vector3D(float a, float b);
    Vector3D(float a, float b, float c);

    float dotProduct(const Vector3D& vec2);
    Vector3D crossProduct(const Vector3D& vec2);
    float length() const;
    float squareLength() const;
    void normalize();
    Vector3D normalized() const;

    void change(float a, float b, float c);
    void change(const Vector3D& vec2);
    void changeX(float a);
    void changeY(float a);
    void changeZ(float a);

    Vector3D operator+(const float num) const;
    Vector3D operator-(const float num) const;
    Vector3D operator*(const float num) const;
    Vector3D operator/(const float num) const;

    Vector3D operator+(const Vector3D& vec2) const;
    Vector3D operator-(const Vector3D& vec2) const;
    Vector3D operator*(const Vector3D& vec2) const;
    Vector3D operator/(const Vector3D& vec2) const;

    Vector3D& operator+=(const float num);
    Vector3D& operator-=(const float num);
    Vector3D& operator*=(const float num);
    Vector3D& operator/=(const float num);

    Vector3D& operator+=(const Vector3D& vec2);
    Vector3D& operator-=(const Vector3D& vec2);
    Vector3D& operator*=(const Vector3D& vec2);
    Vector3D& operator/=(const Vector3D& vec2);

    bool operator==(const Vector3D vec2) const;
    bool operator!=(const Vector3D vec2) const;

    /**
     * @brief rotateAboutX
     * @param angle en radiants
     * @return
     */
    Vector3D& rotateAboutX(float angle);

    /**
     * @brief rotateAboutY
     * @param angle en radiants
     * @return
     */
    Vector3D& rotateAboutY(float angle);

    /**
     * @brief rotateAboutZ
     * @param angle en radiants
     * @return
     */
    Vector3D& rotateAboutZ(float angle);
    Vector3D& rotateAboutAxis(float angle, const Vector3D& axis);

    friend std::ostream& operator<<(std::ostream& out, const Vector3D& vec);

    float distance(const Vector3D& vec2) const;
    float Squaredistance(const Vector3D& vec2) const;


};

#endif // VECTOR3D_H
