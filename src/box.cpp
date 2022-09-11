#include "../include/box.hpp"

bool check_intersection(const Box box, const Vector3 point) {
    /*
	if (point.x > box.position.x && point.x < box.position.x + box.size.x) {
		if (point.y > box.position.y && point.y < box.position.y + box.size.y) {
			if (point.z > box.position.z && point.z < box.position.z + box.size.z) {
				return true;
			}
		}
	}
	return false;
    */
    double xdistsqrd = std::pow(box.position.x-point.x, 2);
    double ydistsqrd = std::pow(box.position.y-point.y, 2);
    double zdistsqrd = std::pow(box.position.z-point.z, 2);
    double distance = std::sqrt(xdistsqrd + ydistsqrd + zdistsqrd);
    if (distance < box.radius)
        return true;
    return false;
}

Box nobox() {
	return Box{Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.0};
}
