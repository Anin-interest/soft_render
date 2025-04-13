#pragma once
#include "vector4.h"

class Matrix
{
public:
    float ele[16];

    // constructors
    Matrix() { normalize(); }
    Matrix(float e0, float e1, float e2, float e3,
        float e4, float e5, float e6, float e7,
        float e8, float e9, float e10, float e11,
        float e12, float e13, float e14, float e15);
    Matrix(const float* rhs);
    Matrix(const Matrix& rhs);
    ~Matrix() = default;

    // setter,getter
    void setelement(int position, float value);
    float getelement(int position) const;
    Vector4 row(int position) const;
    Vector4 col(int position) const;
    void normalize();
    void zero();

    // overloaded operators
    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;
    Matrix operator*(const float rhs) const;
    Matrix operator/(const float rhs) const;
    bool operator==(const Matrix& rhs) const;
    bool operator!=(const Matrix& rhs) const;
    void operator+=(const Matrix& rhs);
    void operator-=(const Matrix& rhs);
    void operator*=(const Matrix& rhs);
    void operator*=(const float rhs);
    void operator/=(const float rhs);
    Matrix operator-() const;
    Matrix operator+() const { return (*this); }
    Vector4 operator*(const Vector4 rhs) const;


    // inverse, transpose
    float determinant() const;
	float getDeterminant() const { return determinant(); }
    void inverted();
    Matrix getInverse() const;
    void transpose();
    Matrix getTranspose() const;
    void invertTranspose();
    Matrix getInverseTranspose() const;

    // operation on space
    void translation(const Vector3& translation);
    void scale(const Vector3& scale);
    void rotationAxis(const double angle, const Vector3& axis);
    void rotationX(const double angle);
    void rotationY(const double angle);
    void rotationZ(const double angle);
    void rotationEuler(const double angleX, const double angleY, const double angleZ);
    void perspective(float fovy, float aspect, float near, float far);
    void perspective(float left, float right, float bottom, float top, float near, float far);
    void ortho(float left, float right, float bottom, float top, float near, float far);
    void lookat(Vector3 cameraPos, Vector3 target, Vector3 worldUp);
	void viewPort(int left, int top, int width, int height);
};