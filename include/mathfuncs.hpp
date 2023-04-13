#pragma once
#include <iostream>
#include <math.h>
#define PI 3.14159265

struct Vector2 {

	double x;
	double y;

	Vector2() :x(0.0),y(0.0) {};
	Vector2(double x, double y) :x(x),y(y) {};


	void operator+=(Vector2 other) {
		x += other.x; 
		y += other.y;
	}

	void operator-=(Vector2 other) {
		x -= other.x; 
		y -= other.y;
	}	

	Vector2 operator+(Vector2 other) {
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(Vector2 other) {
		return Vector2(x - other.x, y - other.y);
	}	

	Vector2 operator*(Vector2 other) {
		return Vector2(x * other.x, y * other.y);
	}

	Vector2 operator/(Vector2 other) {
		return Vector2(x / other.x, y / other.y);
	}	



	Vector2 operator+(double other) {
		return Vector2(x + other, y + other);
	}

	Vector2 operator-(double other) {
		return Vector2(x - other, y - other);
	}	

	Vector2 operator*(double other) {
		return Vector2(x * other, y * other);
	}

	Vector2 operator*(float other) {
		return Vector2(x * other, y * other);
	}

	Vector2 operator/(double other) {
		return Vector2(x / other, y / other);
	}	
	//strange functions

	void fromRadian(double radian) {
		x = cos(radian);
		y = sin(radian);
	}

	double magnitude() {
		return sqrt((x*x) + (y*y));
	}

	Vector2 normalize() {
		double mag = 1/magnitude();
		return Vector2(x,y) * mag;
	}

	Vector2 cross(Vector2 other) {
		return Vector2(x*other.y,y*other.x);
	}

	double dot(Vector2 other) {
		return x*other.x + y*other.y;
	}

};

std::ostream& operator<<(std::ostream& os, Vector2 vec);
