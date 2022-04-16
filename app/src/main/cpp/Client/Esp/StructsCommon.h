#ifndef STRUCTSCOMM_H
#define STRUCTSCOMM_H
#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
#include <list>
using namespace std;

#define maxplayerCount 54
#define maxvehicleCount 54
#define maxitemsCount 200

class Color {
public:
	float r;
	float g;
	float b;
	float a;

	Color() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->a = 0;
	}

	Color(float r, float g, float b, float a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Color(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 255;
	}
	
	static Color Black(){
		return Color(0, 0, 0);
	}

	static Color White(){
		return Color(255, 255, 255);
	}

	static Color Green(){
		return Color(0, 255, 0);
	}
	
	static Color Blue(){
		return Color(0, 0, 255);
	}
	
	static Color Cyan(){
		return Color(0, 255, 255);
	}
	
	static Color DarkGolden(){
		return Color(218,165,32);
	}
	
	static Color Indigo(){
		return Color(75,0,130);
	}
	
	static Color Purple(){
		return Color(128,0,128);
	}
	
	static Color Pink() {
		return Color(255,192,203);
	}
	
	static Color Red() {
		return Color(255, 0, 0);
	}
	
	static Color Yellow() {
		return Color(255, 255, 0);
	}
	
	static Color Magenta() {
		return Color(255, 0, 255);
	}
};

class Rect {
public:
	float x;
	float y;
	float width;
	float height;

	Rect() {
		this->x = 0;
		this->y = 0;
		this->width = 0;
		this->height = 0;
	}

	Rect(float x, float y, float width, float height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	bool operator==(const Rect &src) const {
		return (src.x == this->x && src.y == this->y && src.height == this->height &&
				src.width == this->width);
	}

	bool operator!=(const Rect &src) const {
		return (src.x != this->x && src.y != this->y && src.height != this->height &&
				src.width != this->width);
	}
};

#endif
