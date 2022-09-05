#include "../include/ray.hpp"

col_info ray_march(const Vector3 position, const Vector3 direction, const std::vector<Box> boxes) {
	#define STEP_DISTANCE 5.0
	#define MAX_DEPTH 50
	for (int depth = 0; depth < MAX_DEPTH; depth ++) {
		Vector3 point = position + direction.scale(depth * STEP_DISTANCE);
		for (auto box : boxes) {
			if (check_intersection(box, point)) {
				// so that point does not end up inside the box
				return col_info{true, box, position + direction.scale((depth - 1) * STEP_DISTANCE)}; 
			}
		}
	}
	return col_info{false, nobox(), Vector3(0, 0, 0)};
}
