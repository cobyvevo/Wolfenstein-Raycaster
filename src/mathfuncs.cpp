#include "mathfuncs.hpp"

std::ostream& operator<<(std::ostream& os, Vector2 vec) {
	return os << "Vec2[" << vec.x << " , " << vec.y << "]";
}