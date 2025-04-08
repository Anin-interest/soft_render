#include "matrix.h"
#include "math.h"

void Matrix::set(float e, int x, int y) {
    ele[x][y] = e;
}

Matrix Matrix::operator+(const Matrix& mat) {
    Matrix res(*this);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.ele[i][j] += mat.ele[i][j];
        }
    }
    return res;
}
Matrix Matrix::operator-(const Matrix& mat) {
    Matrix res(*this);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.ele[i][j] -= mat.ele[i][j];
        }
    }
    return res;
}
Matrix Matrix::operator*(float k) {
    Matrix res(*this);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.ele[i][j] *= k;
        }
    }
    return res;
}
Matrix Matrix::operator*(const Matrix& mat) {
    Matrix res(*this);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float sum = 0;
            for (int k = 0; k < 4; k++)
                sum += res.ele[i][k] * mat.ele[k][j];
            res.ele[i][j] = sum;
        }
    }
    return res;
}
Vector4D Matrix::operator*(const Vector4D vec) {
    Vector4D res;
    res.x = ele[0][0] * vec.x + ele[0][1] * vec.y + ele[0][2] * vec.z + ele[0][3] * vec.w;
    res.y = ele[1][0] * vec.x + ele[1][1] * vec.y + ele[1][2] * vec.z + ele[1][3] * vec.w;
    res.z = ele[2][0] * vec.x + ele[2][1] * vec.y + ele[2][2] * vec.z + ele[2][3] * vec.w;
    res.w = ele[3][0] * vec.x + ele[3][1] * vec.y + ele[3][2] * vec.z + ele[3][3] * vec.w;
    return res;
}
Matrix Matrix::operator/(float k) {
    if (k == 0.0f) {
        Matrix res;
        return res;
    }
    Matrix res(*this);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.ele[i][j] /= k;
        }
    }
    return res;
}
void Matrix::operator+=(const Matrix& mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->ele[i][j] += mat.ele[i][j];
        }
    }
}
void Matrix::operator-=(const Matrix& mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->ele[i][j] -= mat.ele[i][j];
        }
    }
}
void Matrix::operator*=(const float k) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->ele[i][j] *= k;
        }
    }
}
void Matrix::operator*=(const Matrix& mat) {
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float sum = 0;
            for (int k = 0; k < 4; k++)
                sum += ele[i][k] * mat.ele[k][j];
            ele[i][j] = sum;
        }
    }
}
void Matrix::operator/=(const float k) {
    if (k == 0.0f) {
        Matrix res;
        for (int i = 0; i < 4; i++)for (int j = 0; j < 4; j++)this->ele[i][j] = 0;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->ele[i][j] /= k;
        }
    }
}
Matrix Matrix::operator+() const {
    return *this;
}
Matrix Matrix::operator-() const {
    Matrix res(*this);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.ele[i][j] = this->ele[i][j] * (-1);
        }
    }
    return res;
}

void Matrix::normalize() {
    for (int i = 0; i < 4; i++)for (int j = 0; j < 4; j++)ele[i][j] = 0;
    for (int i = 0; i < 4; i++)ele[i][i] = 1;
}
void Matrix::transposition() {
    Matrix tmp;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            tmp.ele[i][j] = ele[j][i];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            ele[i][j] = tmp.ele[i][j];
}
void Matrix::translation(const Vector3D& trans) {
    normalize();
    ele[0][3] = trans.x;
    ele[1][3] = trans.y;
    ele[2][3] = trans.z;
}
void Matrix::scale(const Vector3D& sca) {
    normalize();
    ele[0][0] *= sca.x;
    ele[1][1] *= sca.y;
    ele[2][2] *= sca.z;
}
void Matrix::rotationX(const double angle) {
    normalize();
    float a = static_cast<float>(angle);
    ele[1][1] = cosf(a);
    ele[1][2] = -sinf(a);
    ele[2][1] = sinf(a);
    ele[2][2] = cosf(a);
}
void Matrix::rotationY(const double angle) {
    normalize();
    float a = static_cast<float>(angle);
    ele[0][0] = cosf(a);
    ele[0][2] = sinf(a);
    ele[2][0] = -sinf(a);
    ele[2][2] = cosf(a);
}
void Matrix::rotationZ(const double angle) {
    normalize();
    float a = static_cast<float>(angle);
    ele[0][0] = cosf(a);
    ele[0][1] = -sinf(a);
    ele[1][0] = sinf(a);
    ele[1][1] = cosf(a);
}