#pragma once
#include "vector2.h"

class Vector4; // Forward declaration
class Vector3
{
public:
    float x, y, z;

    Vector3() :x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float x, float y, float z) :x(x), y(y), z(z) {}
    Vector3(const float* rhs) :x(*rhs), y(*(rhs + 1)), z(*(rhs + 2)) {}
    Vector3(const Vector3& rhs) :x(rhs.x), y(rhs.y), z(rhs.z) {}
    Vector3(const Vector4& rhs);
    ~Vector3() = default;

    void normalize();
    Vector3 getNormalize() const;
    float length() const { return static_cast<float>(sqrt(x * x + y * y + z * z)); }
    float squaredlength() const { return x * x + y * y + z * z; }
    Vector3 lerp(const Vector3& v2, float weight) const { return (*this) * (1.0f - weight) + v2 * weight; }
    Vector3 quadraticinterpolate(const Vector3& v2, const Vector3& v3, float weight) const
    {
        return (*this) * (1.0f - weight) * (1.0f - weight) + v2 * 2.0f * weight * (1.0f - weight) + v3 * weight * weight;
    }

    float dot(const Vector3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
    Vector3 cross(const Vector3& rhs) const
    {
        return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
    }

    Vector3 operator+(const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
    Vector3 operator-(const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
    Vector3 operator*(const float rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
    Vector3 operator/(const float rhs) const { return (equal(rhs, 0.0f)) ? Vector3(0.0f, 0.0f, 0.0f) : Vector3(x / rhs, y / rhs, z / rhs); }
    bool operator==(const Vector3& rhs) const { return (equal(x, rhs.x) && equal(y, rhs.y) && equal(z, rhs.z)); }
    bool operator!=(const Vector3& rhs) const { return !((*this) == rhs); }
    void operator+=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; }
    void operator-=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; }
    void operator*=(const float rhs) { x *= rhs; y *= rhs; z *= rhs; }
    void operator/=(const float rhs) { if (!equal(rhs, 0.0f)) { x /= rhs; y /= rhs; z /= rhs; } }
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    Vector3 operator+() const { return *this; }
    Vector3 operator()(const Vector4& rhs);
};
