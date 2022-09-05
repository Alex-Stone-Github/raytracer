#pragma once

#include <iostream>
#include <vector>

#include "../include/box.hpp"
#include "../include/vector3.hpp"

struct col_info {
	bool collided;
	Box box;
	Vector3 point;
};

col_info ray_march(const Vector3 position, const Vector3 direction, const std::vector<Box> boxes);
