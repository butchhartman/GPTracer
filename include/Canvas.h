#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <malloc.h>
#include <string.h>
#include "Tuple.h"

typedef struct {
	int width;
	int height;
	Tuple *pixels;
} Canvas;


/*
* Creates a canvas with the passed width and height. All pixel data is initialized to black.
* 
* \param width - The width of the canvas in pixels
* \param height - The height of the canvas in pixels
* 
* \return A canvas struct of the passed length/height and pixel data intialized to black.
*/
Canvas canvas_createCanvas(int width, int height);

/*
* Gets the color value of a canvas at (width, height).
* 
* \param canvas - The canvis to query
* \param width - X coordinate of queried pixel
* \param height - Y coordinate of queried pixel
* 
* \return A tuple representing the color of the pixel at (width, height)
*/
Tuple canvas_pixelAt(Canvas canvas, int width, int height);

/*
* Writes a color to a canvas pixel at (width, height).
* 
* \param *canvas - Pointer to the canvas to write to
* \param color - A tuple representing the color to write
* \param width - X coordinate of queried pixel
* \param height - Y coordinate of queried pixel
*/
void canvas_writePixel(Canvas *canvas, Tuple color, int width, int height);

/*
* Takes the data contained in a canvas struct and converts it to PPM data
* 
* \param canvas - The canvas whose data will be converted
* \param *dataLength - A pointer to an int value that will be assigned the length of the returned data array. (Always 4)
* 
* \returns A char** where 0-2 is the PPM header, and 3 is the actualy PPM color data
*/
char **canvas_canvasToPPM(Canvas canvas, int *dataLength);

/*
* Clamps the passed value to 0-255
* 
* \param num - The float to be clamped
* 
* \return An integer between 0-255
*/
int canvas_RGBClamp(float num);
