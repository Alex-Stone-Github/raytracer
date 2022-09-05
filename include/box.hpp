#pragma once

#include "vector3.hpp"

struct Box {
	Vector3 position;
	Vector3 size;
	Vector3 color;
};
bool check_intersection(const Box box, const Vector3 point);
Box nobox();


