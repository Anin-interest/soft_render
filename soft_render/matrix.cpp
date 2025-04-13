#include "matrix.h"

Matrix::Matrix(float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7, float e8, float e9, float e10, float e11, float e12, float e13, float e14, float e15)
{
    ele[0] = e0;	ele[1] = e1;	ele[2] = e2;	ele[3] = e3;
    ele[4] = e4;	ele[5] = e5;	ele[6] = e6;	ele[7] = e7;
    ele[8] = e8;	ele[9] = e9;	ele[10] = e10;	ele[11] = e11;
    ele[12] = e12;	ele[13] = e13;	ele[14] = e14;	ele[15] = e15;
}

Matrix::Matrix(const float* rhs)
{
	ele[0] = rhs[0];	ele[1] = rhs[1];	ele[2] = rhs[2];	ele[3] = rhs[3];
	ele[4] = rhs[4];	ele[5] = rhs[5];	ele[6] = rhs[6];	ele[7] = rhs[7];
	ele[8] = rhs[8];	ele[9] = rhs[9];	ele[10] = rhs[10];	ele[11] = rhs[11];
	ele[12] = rhs[12];	ele[13] = rhs[13];	ele[14] = rhs[14];	ele[15] = rhs[15];
}

Matrix::Matrix(const Matrix& rhs)
{
	ele[0] = rhs.ele[0];	ele[1] = rhs.ele[1];	ele[2] = rhs.ele[2];	ele[3] = rhs.ele[3];
	ele[4] = rhs.ele[4];	ele[5] = rhs.ele[5];	ele[6] = rhs.ele[6];	ele[7] = rhs.ele[7];
	ele[8] = rhs.ele[8];	ele[9] = rhs.ele[9];	ele[10] = rhs.ele[10];	ele[11] = rhs.ele[11];
	ele[12] = rhs.ele[12];	ele[13] = rhs.ele[13];	ele[14] = rhs.ele[14];	ele[15] = rhs.ele[15];
}

void Matrix::setelement(int position, float value)
{
	if (position < 0 || position > 15) {
		return;
	}
	ele[position] = value;
}

float Matrix::getelement(int position) const
{
	if (position < 0 || position > 15) {
		return 1e9f;
	}
	return ele[position];
}

Vector4 Matrix::row(int position) const
{
    if (position < 0 || position > 3) {
        return Vector4(0);
    }
	return Vector4(ele[position], ele[position + 4], ele[position + 8], ele[position + 12]);
}

Vector4 Matrix::col(int position) const
{
	if (position < 0 || position > 3) {
		return Vector4(0);
	}
	return Vector4(ele[position * 4], ele[position * 4 + 1], ele[position * 4 + 2], ele[position * 4 + 3]);
}

void Matrix::normalize()
{
	zero();
	ele[0] = 1;
	ele[5] = 1;
	ele[10] = 1;
	ele[15] = 1;
}

void Matrix::zero()
{
	for (int i = 0; i < 16; i++) {
		ele[i] = 0;
	}
}

#pragma region overload operator
Matrix Matrix::operator+(const Matrix& rhs) const
{
	return Matrix(
		ele[0] + rhs.ele[0], ele[1] + rhs.ele[1], ele[2] + rhs.ele[2], ele[3] + rhs.ele[3],
		ele[4] + rhs.ele[4], ele[5] + rhs.ele[5], ele[6] + rhs.ele[6], ele[7] + rhs.ele[7],
		ele[8] + rhs.ele[8], ele[9] + rhs.ele[9], ele[10] + rhs.ele[10], ele[11] + rhs.ele[11],
		ele[12] + rhs.ele[12], ele[13] + rhs.ele[13], ele[14] + rhs.ele[14], ele[15] + rhs.ele[15]);
}

Matrix Matrix::operator-(const Matrix& rhs) const
{
    return Matrix(
        ele[0] - rhs.ele[0], ele[1] - rhs.ele[1], ele[2] - rhs.ele[2], ele[3] - rhs.ele[3],
        ele[4] - rhs.ele[4], ele[5] - rhs.ele[5], ele[6] - rhs.ele[6], ele[7] - rhs.ele[7],
        ele[8] - rhs.ele[8], ele[9] - rhs.ele[9], ele[10] - rhs.ele[10], ele[11] - rhs.ele[11],
        ele[12] - rhs.ele[12], ele[13] - rhs.ele[13], ele[14] - rhs.ele[14], ele[15] - rhs.ele[15]);
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
	Matrix res;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float sum = 0;
			for (int k = 0; k < 4; k++)
				sum += ele[i + k * 4] * rhs.ele[k + j * 4];
			res.ele[i + j * 4] = sum;
		}
	}
	return res;
}

Matrix Matrix::operator*(const float rhs) const
{
	return Matrix(
		ele[0] * rhs, ele[1] * rhs, ele[2] * rhs, ele[3] * rhs,
		ele[4] * rhs, ele[5] * rhs, ele[6] * rhs, ele[7] * rhs,
		ele[8] * rhs, ele[9] * rhs, ele[10] * rhs, ele[11] * rhs,
		ele[12] * rhs, ele[13] * rhs, ele[14] * rhs, ele[15] * rhs);
}

Matrix Matrix::operator/(const float rhs) const
{
	return Matrix(
		ele[0] / rhs, ele[1] / rhs, ele[2] / rhs, ele[3] / rhs,
		ele[4] / rhs, ele[5] / rhs, ele[6] / rhs, ele[7] / rhs,
		ele[8] / rhs, ele[9] / rhs, ele[10] / rhs, ele[11] / rhs,
		ele[12] / rhs, ele[13] / rhs, ele[14] / rhs, ele[15] / rhs);
}

bool Matrix::operator==(const Matrix& rhs) const
{
	for (int i = 0; i < 16; i++) {
		if (ele[i] != rhs.ele[i]) {
			return false;
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix& rhs) const
{
	for (int i = 0; i < 16; i++) {
		if (ele[i] != rhs.ele[i]) {
			return true;
		}
	}
	return false;
}

void Matrix::operator+=(const Matrix& rhs)
{
	for (int i = 0; i < 16; i++) {
		ele[i] += rhs.ele[i];
	}
}

void Matrix::operator-=(const Matrix& rhs)
{
	for (int i = 0; i < 16; i++) {
		ele[i] -= rhs.ele[i];
	}
}

void Matrix::operator*=(const Matrix& rhs)
{
	Matrix res;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float sum = 0;
			for (int k = 0; k < 4; k++)
				sum += ele[i + k * 4] * rhs.ele[k + j * 4];
			res.ele[i + j * 4] = sum;
		}
	}
	for (int i = 0; i < 16; i++) {
		ele[i] = res.ele[i];
	}
}

void Matrix::operator*=(const float rhs)
{
	for (int i = 0; i < 16; i++) {
		ele[i] *= rhs;
	}
}

void Matrix::operator/=(const float rhs)
{
	for (int i = 0; i < 16; i++) {
		ele[i] /= rhs;
	}
}

Matrix Matrix::operator-() const
{
	return Matrix(
		-ele[0], -ele[1], -ele[2], -ele[3],
		-ele[4], -ele[5], -ele[6], -ele[7],
		-ele[8], -ele[9], -ele[10], -ele[11],
		-ele[12], -ele[13], -ele[14], -ele[15]);
}

Vector4 Matrix::operator*(const Vector4 rhs) const
{
	Vector4 res;
	res.x = ele[0] * rhs.x + ele[4] * rhs.y + ele[8] * rhs.z + ele[12] * rhs.w;
	res.y = ele[1] * rhs.x + ele[5] * rhs.y + ele[9] * rhs.z + ele[13] * rhs.w;
	res.z = ele[2] * rhs.x + ele[6] * rhs.y + ele[10] * rhs.z + ele[14] * rhs.w;
	res.w = ele[3] * rhs.x + ele[7] * rhs.y + ele[11] * rhs.z + ele[15] * rhs.w;
	return res;
}
#pragma endregion

#pragma region basic options
void Matrix::translation(const Vector3& translation)
{
	normalize();
	ele[12] = translation.x;
	ele[13] = translation.y;
	ele[14] = translation.z;
}

void Matrix::scale(const Vector3& scale)
{
	normalize();
	ele[0] = scale.x;
	ele[5] = scale.y;
	ele[10] = scale.z;
}
#pragma endregion

#pragma region rotations
void Matrix::rotationAxis(const double angle, const Vector3& axis)
{
	normalize();
	Vector3 u = axis.getNormalize();
	float a = static_cast<float>(PI * angle / 180);
	float sinAngle = static_cast<float>(sin(a));
	float cosAngle = static_cast<float>(cos(a));
	float oneMinusCosAngle = 1.0f - cosAngle;
	ele[0] = (u.x) * (u.x) + cosAngle * (1 - (u.x) * (u.x));
	ele[4] = (u.x) * (u.y) * (oneMinusCosAngle)-sinAngle * u.z;
	ele[8] = (u.x) * (u.z) * (oneMinusCosAngle)+sinAngle * u.y;
	ele[1] = (u.x) * (u.y) * (oneMinusCosAngle)+sinAngle * u.z;
	ele[5] = (u.y) * (u.y) + cosAngle * (1 - (u.y) * (u.y));
	ele[9] = (u.y) * (u.z) * (oneMinusCosAngle)-sinAngle * u.x;
	ele[2] = (u.x) * (u.z) * (oneMinusCosAngle)-sinAngle * u.y;
	ele[6] = (u.y) * (u.z) * (oneMinusCosAngle)+sinAngle * u.x;
	ele[10] = (u.z) * (u.z) + cosAngle * (1 - (u.z) * (u.z));
}

void Matrix::rotationX(const double angle)
{
	normalize();
	float a = static_cast<float>(PI * angle / 180);
	ele[5] = cosf(a);
	ele[6] = sinf(a);
	ele[9] = -sinf(a);
	ele[10] = cosf(a);
}

void Matrix::rotationY(const double angle)
{
	normalize();
	float a = static_cast<float>(PI * angle / 180);
	ele[0] = cosf(a);
	ele[2] = -sinf(a);
	ele[8] = sinf(a);
	ele[10] = cosf(a);
}

void Matrix::rotationZ(const double angle)
{
	normalize();
	float a = static_cast<float>(PI * angle / 180);
	ele[0] = cosf(a);
	ele[1] = sinf(a);
	ele[4] = -sinf(a);
	ele[5] = cosf(a);
}

void Matrix::rotationEuler(const double angleX, const double angleY, const double angleZ)
{
	rotationX(angleX);
	Matrix tmp;
	tmp.rotationY(angleY);
	*this *= tmp;
	tmp.rotationZ(angleZ);
	*this *= tmp;
}
#pragma endregion

void Matrix::perspective(float fovy, float aspect, float near, float far)
{
	zero();
	float rFovy = fovy * PI / 180;
	const float tanHalfFovy = tanf(static_cast<float>(rFovy * 0.5f));
	ele[0] = 1.0f / (aspect * tanHalfFovy);
	ele[5] = 1.0f / tanHalfFovy;
	ele[10] = -((far + near) / (far - near));
	ele[11] = -1.f;
	ele[14] = -(2.0f * far * near) / (far - near);
}

void Matrix::perspective(float left, float right, float bottom, float top, float near, float far)
{
	zero();
	ele[0] = 2.0f * near / (right - left);
	ele[5] = 2.0f * near / (top - bottom);
	ele[8] = (right + left) / (right - left);
	ele[9] = (top + bottom) / (top - bottom);
	ele[10] = -(far + near) / (far - near);
	ele[11] = -1.0f;
	ele[14] = -(2.0f * far * near) / (far - near);
}

void Matrix::ortho(float left, float right, float bottom, float top, float near, float far)
{
	normalize();
	ele[0] = 2.0f / (right - left);
	ele[5] = 2.0f / (top - bottom);
	ele[10] = -2.0f / (far - near);	
	ele[14] = -(far + near) / (far - near);
}

void Matrix::lookat(Vector3 cameraPos, Vector3 target, Vector3 worldUp)
{
	normalize();
	Vector3 zAxis = (cameraPos - target).getNormalize();
	Vector3 xAxis = worldUp.cross(zAxis).getNormalize();
	Vector3 yAxis = zAxis.cross(xAxis).getNormalize();
	ele[0] = xAxis.x;
	ele[1] = yAxis.x;
	ele[2] = zAxis.x;

	ele[4] = xAxis.y;
	ele[5] = yAxis.y;
	ele[6] = zAxis.y;

	ele[8] = xAxis.z;
	ele[9] = yAxis.z;
	ele[10] = zAxis.z;

	ele[12] = -xAxis.dot(cameraPos);
	ele[13] = -yAxis.dot(cameraPos);
	ele[14] = -zAxis.dot(cameraPos);
}

void Matrix::viewPort(int left, int top, int width, int height)
{
	normalize();
	ele[0] = static_cast<float>(width) / 2.0f;
	ele[5] = -static_cast<float>(height) / 2.0f;
	ele[12] = static_cast<float>(left) + static_cast<float>(width) / 2.0f;
	ele[13] = static_cast<float>(top) + static_cast<float>(height) / 2.0f;
}

