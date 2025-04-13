#include "vector3.h"
#include "math.h"

Vector3 Vector3::getNormalize() const {
    float tmp = this->length();
    if (equal(tmp, 0.0)) return Vector3(0.0f, 0.0f, 0.0f);
    Vector3 res(x / tmp, y / tmp, z / tmp);
    return res;
}

void Vector3::normalize() {
    float tmp = this->length();
	if (equal(tmp, 0.0f)) return;
    x /= tmp;
    y /= tmp;
    z /= tmp;
}
