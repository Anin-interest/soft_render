#pragma once
#include "include.h"

float constexpr PI = 3.1415926535;
float constexpr EU = 2.7182818284;

#define rep(x, a, b) for (int x = (a), _n = int(b); x < _n; ++x)

// 注意 insd 是开区间，clmp 闭区间。
template<class T>
bool insd(T v, T a, T b) { return v >= a && v < b; }
template<class T>
T const& clmp(T v, T a, T b) { return min(b, max(a, v)); }

inline int mod(int a, int b) { return (a % b + b) % b; }
inline float modf(float a, float b) { return fmod(fmod(a, b) + b, b); }
inline float modp(float an) { return modf(an + PI, 2 * PI) - PI; }

// 注意 [a, b] 是闭区间，但 sz 是开的。
int drnd(int a, int b);
int drnd(int sz);
float frnd(float a, float b);
float frnd(float b);
float nrnd(float mean, float stddev);

// 精度差
inline bool equal(float a, float b) { return fabs(a - b) < 1e-9; }
