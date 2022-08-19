#pragma once

#include <iostream>
#include <vector>

#include "../include/box.hpp"
#include "../include/vector3.hpp"

struct CollisionInfo {
	Box collider;
	Vector3 position;
	bool collided;
};
struct CollisionInfo ray_march(const Vector3 position, const Vector3 direction, const std::vector<Box> boxes);
