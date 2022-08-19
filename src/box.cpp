#include "../include/box.hpp"

bool check_intersection(const Box box, const Vector3 point) {
	if (point.x > box.position.x && point.x < box.position.x + box.size.x) {
		if (point.y > box.position.y && point.y < box.position.y + box.size.y) {
			if (point.z > box.position.z && point.z < box.position.z + box.size.z) {
				return true;
			}
		}
	}
	return false;
}