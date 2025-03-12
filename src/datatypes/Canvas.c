#include "Canvas.h"


Canvas canvas_createCanvas(int width, int height) {
	Canvas newCanvas = { 0 };
	newCanvas.width = width;
	newCanvas.height = height;
	newCanvas.pixels = (Tuple*)malloc(sizeof(Tuple) * newCanvas.width * newCanvas.height);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			newCanvas.pixels[i * width + j] = tuple_createColor(0, 0, 0);
		}
	}

	return newCanvas;
}

Tuple canvas_pixelAt(Canvas canvas, int width, int height)
{
	return canvas.pixels[height * canvas.width + width];
}

void canvas_writePixel(Canvas *canvas, Tuple color, int width, int height)
{
	canvas->pixels[height * canvas->width + width] = color;
}

char** canvas_canvasToPPM(Canvas canvas, int *dataLength)
{
	char **PPMdata = malloc(sizeof(char*) * 4);

	if (PPMdata == NULL) {
		printf("Memory allocation failed!\n");
		return NULL;
	}

	char magicNumber[4] = "P3\n\0";

	char sizeIdentifier[100]; // temp hack length
	sprintf(sizeIdentifier, "%d", canvas.width);

	char sizeTemp[100];
	sprintf(sizeTemp, "%d", canvas.height);

	strcat(sizeIdentifier, " ");
	strcat(sizeIdentifier, sizeTemp);
	strcat(sizeIdentifier, "\n\0");

	char maxRGBVal[5] = "255\n\0";

//	printf("%d", sizeof(magicNumber));

	PPMdata[0] = malloc(sizeof(magicNumber));
	strcpy(PPMdata[0], magicNumber);

	PPMdata[1] = malloc(sizeof(sizeIdentifier));
	strcpy(PPMdata[1], sizeIdentifier);

	PPMdata[2] = malloc(sizeof(maxRGBVal));
	strcpy(PPMdata[2], maxRGBVal);

	PPMdata[3] = malloc(sizeof(char) * canvas.width * canvas.height * 4 * 3 + 1); // *4 because each number is 4 chars long *3 because three nums per pixel +1 for \0
	
	// Removes the \0 at the beginning of the string
	strcpy(PPMdata[3], "");

	// Populate string with data
	int curH = 0;
	for (int i = 0; i < canvas.width * canvas.height; i++) {
		curH = (int)(i / canvas.width);
		for (int j = 0; j < 3; j++) {
			char num[5];
			int colorVal;
			if (j == 0) {
				colorVal = canvas_RGBClamp(canvas_pixelAt(canvas, i % canvas.width, curH).x * 255);
			}
			else if (j == 1) {
				colorVal = canvas_RGBClamp(canvas_pixelAt(canvas, i % canvas.width, curH).y * 255);
			}
			else if (j == 2) {
				colorVal = canvas_RGBClamp(canvas_pixelAt(canvas, i % canvas.width, curH).z * 255);
			}

			// have at most 70 characters on one line to conform to PPM standards. (the plus one is two avoid the first number (i=0) having a newline)
			if ( ((i + 1) % 5 == 0 && j == 2) || ((i+1) % (canvas.width) == 0 && j == 2) ) {
				sprintf(num, "%d\n", colorVal);
			}
			else if (i == canvas.width * canvas.height - 1 && j == 2) { // Leave off the space on the last entry
				sprintf(num, "%d", colorVal);
			}
			else {
				sprintf(num, "%d ", colorVal);
			}
			strcat(PPMdata[3], num);
		}
	}

	// Terminate string
	//strcat(PPMdata[3], "\0");

	//*dataLength = 4;

	return PPMdata;

	/*
	char** PPMdata = (char**)malloc(sizeof(char*) * canvas.width * canvas.height + sizeof(char*) * 3); //(sizeof(char) * canvas.width * canvas.height + sizeof(char) * 7 * ((int)log10(canvas.width)+1 + 2 + (int)log10(canvas.height) + 1)) * 50 );
	char *cwidth = malloc(sizeof(char) * canvas.width + sizeof(char) + sizeof(char) * canvas.height);
	char *cheight = malloc(sizeof(char) * canvas.height);
	
	if (PPMdata == NULL || cwidth == NULL || cheight == NULL) {
		return NULL;
	}

	sprintf(cwidth, "%d", canvas.width);
	sprintf(cheight, "%d", canvas.height);
	
	strcat(cwidth, " ");
	strcat(cwidth, cheight);
	strcat(cwidth, "\n");

	free(cheight);
	
	PPMdata[0] = "P3\n";
	PPMdata[1] = cwidth;
	PPMdata[2] = "255\n";
	
	for (int i = 0; i < canvas.height; i++) {
		for (int j = 0; j < canvas.width; j++) {

			char r[4];
			char g[4];
			char b[4];

			sprintf(r, "%d",  (int)(canvas_pixelAt(canvas, j, i).x * 1 ) );
			sprintf(g, "%d", (int)(canvas_pixelAt(canvas, j, i).y * 1 ) );
			sprintf(b, "%d", (int)(canvas_pixelAt(canvas, j, i).z * 1) );

			printf("R: %s G: %s B: %s\n", r, g, b);

			PPMdata[i * canvas.width + j + 3] = malloc(sizeof(char) * 4);
			PPMdata[i * canvas.width + j + 4] = malloc(sizeof(char) * 4); // False positive warning ?
			PPMdata[i * canvas.width + j + 5] = malloc(sizeof(char) * 4);

			if (PPMdata[i * canvas.width + j + 3] == NULL || PPMdata[i * canvas.width + j + 4] == NULL || PPMdata[i * canvas.width + j + 5] == NULL) {
				return NULL;
			}

			if ((i + j+3) % 70 == 0) {
				strcat(r, "\n");
			}
			else {
				strcat(r, " ");
			}
			if ((i + j + 4) % 70 == 0) {
				strcat(g, "\n");
			}
			else {
				strcat(g, " ");
			}
			if ((i + j + 5) % 70 == 0) {
				strcat(b, "\n");
			}
			else {
				strcat(b, " ");
			}

			strcpy(PPMdata[i * canvas.width + j + 3], r);
			strcpy(PPMdata[i * canvas.width + j + 4], g);
			strcpy(PPMdata[i * canvas.width + j + 5], b);
		}
	}

	*dataLength = canvas.width * canvas.height + 3;

	return PPMdata;
	*/
}

int canvas_RGBClamp(float num) {
	int clamped;
	if (num >= 255) {
		clamped = 255;
	}
	else if (num < 0){
		clamped = 0;
	}
	else {
		clamped =(int)num;
	}
 
	return clamped;
}

