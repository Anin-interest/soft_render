#pragma once
#include "utils.h"

class Vector2
{
public:
	float x, y;

	// constructors
	Vector2() :x(0), y(0) {};
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2(const float* rhs) :x(*rhs), y((*rhs) + 1) {}
	Vector2(const Vector2& rhs) :x(rhs.x), y(rhs.y) {}
	~Vector2() = default;

	// normalization
	void normalize();
	Vector2 getNormalize()const;
	// length calculation
	float length() const { return static_cast<float>(sqrt(x * x + y * y)); }
	float squaredlength()const { return static_cast<float>(x * x + y * y); }
	// linear interpolation
	Vector2 lerp(const Vector2& v2, const float weight)const { return (*this) * (1.0f - weight) + v2 * weight; }
	Vector2 quadraticinterpolate(const Vector2& v2, const Vector2& v3, const float weight) const
	{
		return (*this) * (1.0f - weight) * (1.0f - weight) + v2 * 2.0f * weight * (1.0f - weight) + v3 * weight * weight;
	}

	// overloaded operators
	Vector2 operator+(const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
	Vector2 operator-(const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
	Vector2 operator*(const float rhs) const { return Vector2(x * rhs, y * rhs); }
	Vector2 operator/(const float rhs) const { return equal(rhs, 0.0) ? Vector2(0.0f, 0.0f) : Vector2(x / rhs, y / rhs); }

	bool operator==(const Vector2& rhs) const { return (equal(x, rhs.x) && equal(y, rhs.y)); }
	bool operator!=(const Vector2& rhs) const { return !((*this) == rhs); }

	void operator+=(const Vector2& rhs) { x += rhs.x;	y += rhs.y; }
	void operator-=(const Vector2& rhs) { x -= rhs.x;	y -= rhs.y; }
	void operator*=(const float rhs) { x *= rhs; y *= rhs; }
	void operator/=(const float rhs) { if (!equal(rhs, 0.0)) { x /= rhs; y /= rhs; } }

	Vector2 operator-() const { return Vector2(-x, -y); }
	Vector2 operator+() const { return *this; }
};
