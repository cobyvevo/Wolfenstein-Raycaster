#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <map>

#include "canvas.hpp"
#include "worldrenderer.hpp"

int main(int argc, char* args[]) {
	std::cout << "im a gamer" << std::endl;
	if (SDL_Init(SDL_INIT_EVERYTHING)<0) {
		std::cout << "INIT Failed" << SDL_GetError() << std::endl;
	}

	CanvasWindow window(700,700,5);
	
	Scene test_scene({
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,0,0,0,0,1,
		1,0,0,0,1,0,0,0,0,1,
		1,0,0,0,1,1,1,0,0,1,
		1,0,1,0,0,0,0,0,0,1,
		1,0,1,1,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
	},10,10);

	CameraInfo camera;
	camera.position = Vector2(1,1);
	
	WorldRenderer world(&test_scene, &camera, window.pixel_width);


	std::map<int, bool> keyboard;
	bool running = true;
	SDL_Event event;

	ColorRGBA red(255,0,0,255);
	ColorRGBA white(255,255,255,255);
	ColorRGBA blue(0,0,255,255);
	ColorRGBA purple(255,0,255,255);
	

	std::vector<RaycastResult> raycastarray;
	ColorRGBA shade(0,0,0,0);
	while (running) {

		//render
		world.Render(raycastarray);

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			} else
			{
				switch(event.type) // Control values within keyboard array
		        {
			        case SDL_KEYDOWN: 
			            keyboard[event.key.keysym.sym] = true;	               
			            break;
			        case SDL_KEYUP:
			            keyboard[event.key.keysym.sym] = false;
			            break;
		        }
			}
		}	

		//movement

		if (keyboard[SDLK_UP] == true){
			camera.position += camera.vector*0.02;
		} else if (keyboard[SDLK_DOWN] == true){
			camera.position -= camera.vector*0.02;
		}

		if (keyboard[SDLK_LEFT] == true){
			camera.setRot(camera.rotation - 0.03);
		} else if (keyboard[SDLK_RIGHT] == true){
			camera.setRot(camera.rotation + 0.03);
		}

		//window.DebugFrame();
		window.ClearFrame();

		//raycast display
			
		int minimap_multi = 2;
		int screen_pos = 0;

		//draw debug minimap
		for (size_t i = 0; i < test_scene.world.size(); i++) {
			int cell = test_scene.world[i];
			if (cell == 1) window.SetPixels( (i % test_scene.world_width)*minimap_multi , (i / test_scene.world_width)*minimap_multi, minimap_multi, minimap_multi, white);
		}

		for (RaycastResult rayresult : raycastarray) {
			//world
			double current_distance = rayresult.distance;
			if (current_distance < 0.1) continue; // no divisions by 0

			int fog = int(255/(current_distance+1)); //fog as the walls get farther
			shade.r = shade.g = shade.b = fog;

			double wall_height = (window.pixel_height/(current_distance))*0.5; // 0.5 wall height
			
			window.SetPixels(
				screen_pos,
				(window.pixel_height/2) - (wall_height/2),
				1,
				wall_height,
				shade
			);

			//minimap
			window.SetPixel(
				int(rayresult.position.x*minimap_multi), 
				int(rayresult.position.y*minimap_multi),
				shade);

			window.SetPixel(
				int(rayresult.begin.x*minimap_multi), 
				int(rayresult.begin.y*minimap_multi),
				purple);

			screen_pos++;
		}

		window.SetPixel((camera.position.x+(camera.vector.x*0.5))*minimap_multi,(camera.position.y+(camera.vector.y*0.5))*minimap_multi,red);
		window.SetPixel(camera.position.x*minimap_multi,camera.position.y*minimap_multi,red);

		//RaycastResult result = world.Raycast(camera.position,camera.vector);
		//window.SetPixel(result.position.x*minimap_multi,result.position.y*minimap_multi,blue);
	

		window.Draw();

	}

	return 0;
}