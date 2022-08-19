#include "../include/ray.hpp"

struct CollisionInfo ray_march(const Vector3 position, const Vector3 direction, const std::vector<Box> boxes) {
	#define STEP_DISTANCE 10.0
	#define MAX_DEPTH 100
	for (int depth = 0; depth < MAX_DEPTH; depth ++) {
		Vector3 point = position + direction.scale(depth * STEP_DISTANCE);
		for (auto box : boxes) {
			if (check_intersection(box, point)) {
				return {box, point, true};
			}
		}
	}
	return {{Vector3(0,0,0),Vector3(0,0,0)}, position, true};
}
