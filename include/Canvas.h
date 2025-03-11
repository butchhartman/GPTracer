#pragma once
#include <math.h>
#include <malloc.h>
#include <string.h>
#include "Tuple.h"

typedef struct {
	int width;
	int height;
	Tuple *pixels;
} Canvas;

Canvas canvas_createCanvas(int width, int height);
Tuple canvas_pixelAt(Canvas canvas, int width, int height);
void canvas_writePixel(Canvas *canvas, Tuple color, int width, int height);
char **canvas_canvasToPPM(Canvas canvas, int *dataLength);
int canvas_RGBClamp(float num);
