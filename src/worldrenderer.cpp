#include "worldrenderer.hpp"


//Scene

int Scene::Query(int x, int y) {
	int index = (x % world_width) + (y * world_width);
	if (index < 0) return 0;
	if (index > int(world.size())) return 0;
	return world[index];
}

int Scene::Query(Vector2 pos) {
	int x = pos.x; int y = pos.y;
	int index = (x % world_width) + (y * world_width);
	if (index < 0) return 0;
	if (index > int(world.size())) return 0;
	return world[index];
}
//CameraInfo

//RaycastResult

//WorldRenderer

void WorldRenderer::Render(std::vector<RaycastResult> &array) {
	array.clear();

	double half_res = resolution/2;
	Vector2 right(camera->vector.y, -camera->vector.x);

	for (int i = 0; i < resolution; i++) {

		double raychange = (i-half_res);
		double sweep = raychange/half_res;

		Vector2 newvector = camera->vector + right * sweep * -0.5;

		RaycastResult ray = Raycast(camera->position, newvector);
		double real_dist = camera->vector.dot(ray.position-camera->position);
		ray.distance = real_dist;
		
		array.push_back(ray);
	}	
};

RaycastResult WorldRenderer::Raycast(Vector2 position, Vector2 normal, double resolution) {
	RaycastResult result;
	result.position = position;
	result.direction = normal.normalize();
	result.begin = position;

	int steps = 0;

	while (steps < 800) {

		if (current_scene->Query(result.position) != 0) {
			result.hit = true;
			break;
		} 

		result.position += normal * resolution;
		steps++;

	}

	result.distance = steps * resolution;
	
	return result;
};