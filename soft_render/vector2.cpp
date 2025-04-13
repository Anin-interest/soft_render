#include "vector2.h"

void Vector2::normalize() {
    float tmp = this->length();
	if (equal(tmp, 0.0f)) return;
    x /= tmp;
    y /= tmp;
}

Vector2 Vector2::getNormalize() const {
    float tmp = this->length();
	if (equal(tmp, 0.0f)) return Vector2(0.0f, 0.0f);
    Vector2 res(x / tmp, y / tmp);
    return res;
}
