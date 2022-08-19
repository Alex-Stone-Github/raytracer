#pragma once

#include <iostream>
#include <cmath>


class Vector3 {
public:
	double x,y,z;
	Vector3(double x, double y, double z);
	double magnitude() const;
	Vector3 scale(double scaler) const;
	Vector3 norm() const;
	Vector3 operator+(Vector3 other) const;
	Vector3 clone() const;
};
