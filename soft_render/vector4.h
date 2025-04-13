#pragma once
#include "vector3.h"

class Vector4
{
public:
    float x, y, z, w;

    // constructors
    Vector4() :x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vector4(float newX, float newY, float newZ, float newW) :x(newX), y(newY), z(newZ), w(newW) {}
    Vector4(const float* rhs) :x(*rhs), y(*(rhs + 1)), z(*(rhs + 2)), w(*(rhs + 3)) {}
    Vector4(const Vector4& rhs) :x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}
    Vector4(const Vector3& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(1.0f) {}
    ~Vector4() = default;

    // normalization
    void normalize();
    Vector4 getNormalize() const;
    // length caculation
    float length() const { return static_cast<float>(sqrt(x * x + y * y + z * z + w * w)); }
    float squaredlength() const { return x * x + y * y + z * z + w * w; }
    // product
    float dot(const Vector4& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w; }
    // linear interpolation
    Vector4 lerp(const Vector4& v2, float weight) const { return (*this) * (1.0f - weight) + v2 * weight; }
    Vector4 quadraticinterpolate(const Vector4& v2, const Vector4& v3, float weight) const
    {
        return (*this) * (1.0f - weight) * (1.0f - weight) + v2 * 2.0f * weight * (1.0f - weight) + v3 * weight * weight;
    }

    // overloaded operators
    Vector4 operator+(const Vector4& rhs) const { return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
    Vector4 operator-(const Vector4& rhs) const { return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
    Vector4 operator*(const float rhs) const { return Vector4(x * rhs, y * rhs, z * rhs, w * rhs); }
    Vector4 operator/(const float rhs) const
    {
        return (equal(rhs, 0.0f)) ? Vector4(0.0f, 0.0f, 0.0f, 0.0f) : Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
    }

    bool operator==(const Vector4& rhs) const { return (equal(x, rhs.x) && equal(y, rhs.y) && equal(z, rhs.z) && equal(w, rhs.w)); }
    bool operator!=(const Vector4& rhs) const { return !((*this) == rhs); }

    void operator+=(const Vector4& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; }
    void operator-=(const Vector4& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; }
    void operator*=(const float rhs) { x *= rhs; y *= rhs; z *= rhs; w *= rhs; }
    void operator/=(const float rhs) { if (!equal(rhs, 0.0f)) { x /= rhs; y /= rhs; z /= rhs; w /= rhs; } }

    Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }
    Vector4 operator+() const { return *this; }
};