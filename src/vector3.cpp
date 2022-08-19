#include "../include/vector3.hpp"


Vector3::Vector3(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
double Vector3::magnitude() const {
	return std::sqrt(x*x + y*y + z*z);
}
Vector3 Vector3::scale(double scaler) const {
	return Vector3(x*scaler,y*scaler, z*scaler);
}
Vector3 Vector3::norm() const {
	return scale(1/magnitude());
}
Vector3 Vector3::operator+(Vector3 other) const {
	return Vector3(x+other.x, y+other.y, z+other.z);
}
Vector3 Vector3::clone() const {
	return Vector3(x,y,z);
}
