#include "utils.h"

int drnd(int a, int b) {
	static std::random_device rd;
	static std::mt19937 generator(rd());
	std::uniform_int_distribution<int> d(a, b);
	return d(generator);
}
int drnd(int sz) { return drnd(0, sz - 1); }
float frnd(float a, float b) {
	static std::random_device rd;
	static std::mt19937 generator(rd());
	std::uniform_real_distribution<float> d(a, b);
	return d(generator);
}
float frnd(float b) { return frnd(0, b); }
float nrnd(float mean, float stddev) {
	static std::random_device rd;
	static std::mt19937 generator(rd());
	std::normal_distribution<float> d(mean, stddev);
	return d(generator);
}
