#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

struct ColorRGBA {
	ColorRGBA(int r, int g, int b, int a) :r(r),g(g),b(b),a(a) {};
	int r = 0;
	int g = 0;
	int b = 255;
	int a = 255;
};

class CanvasWindow { 

public:

	CanvasWindow(int width, int height, int pixel_size);
	void DebugFrame(); //std::vector<ColorRGBA> display
	void ClearFrame();

	void SetPixel(int px, int py, ColorRGBA col);
	void SetPixels(int px, int py, int pw, int ph, ColorRGBA col);

	void Draw();

	int pixel_size;
	int pixel_width;
	int pixel_height;

private:

	std::vector<ColorRGBA> display;

	SDL_Window* window;
	SDL_Renderer* renderer;

};