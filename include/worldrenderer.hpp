#pragma once
#include "mathfuncs.hpp"
#include <vector>

struct Scene {
	std::vector<int> world;
	int world_width = 0;
	int world_height = 0;

	Scene(std::vector<int> world,int width,int height) :world(world),world_width(width),world_height(height) {};

	int Query(int x, int y);
	int Query(Vector2 pos);
	
};

struct CameraInfo {

	Vector2 position;
	Vector2 vector;
	double rotation = 0;

	void setRot(double new_rotation) { 
		rotation = new_rotation; 
		vector.fromRadian(rotation); 
	};

};

struct RaycastResult {
	bool hit = false;
	float distance = 0;
	Vector2 begin;
	Vector2 position;
	Vector2 direction;
};

class WorldRenderer {

public:

	WorldRenderer(Scene* scene, CameraInfo* camera, int resolution) :current_scene(scene),resolution(resolution),camera(camera) {};
	void Render(std::vector<RaycastResult> &array);

	RaycastResult Raycast(Vector2 position, Vector2 normal, double resolution = 0.01f); 

private:

	Scene* current_scene;
	int resolution = 10;
	CameraInfo* camera;

};