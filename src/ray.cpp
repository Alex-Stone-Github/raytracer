#include "../include/ray.hpp"

bool ray_march(const Vector3 position, const Vector3 direction, const std::vector<Box> boxes) {
	#define STEP_DISTANCE 1.0
	#define MAX_DEPTH 400
	for (int depth = 0; depth < MAX_DEPTH; depth ++) {
		Vector3 point = position + direction.scale(depth * STEP_DISTANCE);
		for (auto box : boxes) {
			if (check_intersection(box, point)) {
				return true; 
			}
		}
	}
	return false;
}
