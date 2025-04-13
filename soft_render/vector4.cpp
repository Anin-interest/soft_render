#include "vector4.h"

void Vector4::normalize()
{
	float tmp = this->length();
	if (equal(tmp, 0.0f)) return;
	x /= tmp;
	y /= tmp;
	z /= tmp;
	w /= tmp;
}

Vector4 Vector4::getNormalize() const
{
	float tmp = this->length();
	if (equal(tmp, 0.0)) return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	return Vector4(x / tmp, y / tmp, z / tmp, w / tmp);
}
