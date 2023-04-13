#include "canvas.hpp"

CanvasWindow::CanvasWindow(int width, int height, int pixel_size) :pixel_size(pixel_size) {

	window = SDL_CreateWindow("raycaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Window Failed" << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL) {
		std::cout << "Renderer Failed" << SDL_GetError() << std::endl;
	}

	pixel_width = width / pixel_size;
	pixel_height = height / pixel_size;

	for (int x = 0; x < pixel_width; x++) {
		for (int y = 0; y < pixel_height; y++) {
			ColorRGBA newcolor(255/(x+1),0,255/(y+1),255);
			display.push_back(newcolor);
		}
	}

}

float pulse = 0;

void CanvasWindow::DebugFrame() {

	int i = 0;

	pulse += 0.1;

	if (pulse > 100) pulse = 0;

	for (int x = 0; x < pixel_width; x++) {
		for (int y = 0; y < pixel_height; y++) { 
			//completely arbritrary color gradient along with pulsing green
			display[i].r = 255/(x+1);
			display[i].g = int(pulse * 25.5);
			display[i].b = 255/(y+1);
			display[i].a = 255;
			i++;
		}
	}

}

void CanvasWindow::ClearFrame() {
	for (int i = 0; i < pixel_width*pixel_height; i++) {
		display[i].r = display[i].g = display[i].b = display[i].a = 0;
	}
}


void CanvasWindow::SetPixel(int px, int py, ColorRGBA col) {
	if (px < 0 || px > pixel_width || py < 0 || py > pixel_height) return;
	display[ (px%pixel_width) + (py*pixel_width) ] = col;
}

void CanvasWindow::SetPixels(int px, int py, int pw, int ph, ColorRGBA col) {
	for (int x = px; x < px+pw; x++) {
		for (int y = py; y < py+ph; y++) {
		
			if (x < 0 || x >= pixel_width || y < 0 || y >= pixel_height) continue;
			display[ (x%pixel_width) + (y*pixel_width) ] = col;

		}
	}
}

void CanvasWindow::Draw() {

	SDL_RenderClear(renderer);

	SDL_Rect r; // create a single rect object to use for all rects
	r.w = pixel_size;
	r.h = pixel_size;

	int i = 0;
	for (ColorRGBA col : display) {

		int x = (i % pixel_width);
		int y = (i / pixel_width);

		r.x = x*pixel_size;
		r.y = y*pixel_size;
		
		SDL_SetRenderDrawColor(renderer, col.r,col.g,col.b,col.a);
		SDL_RenderFillRect(renderer, &r);
		i++;

	}

	SDL_SetRenderDrawColor(renderer, 40,40,40,255);
	SDL_RenderPresent(renderer);


}