#include "Tuple.h"
#include "Canvas.h"
#include "unity.h"
void setUp() {

}

void tearDown() {

}

void test_canvas_createCanvas() {
	Canvas testCanvas = canvas_createCanvas(10, 20);
	TEST_ASSERT_EQUAL_INT(10, testCanvas.width);
	TEST_ASSERT_EQUAL_INT(20, testCanvas.height);
	Tuple black = tuple_createColor(0, 0, 0);
	for (int i = 0; i < testCanvas.width; i++) {
		for (int j = 0; j < testCanvas.height; j++) {
			TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(canvas_pixelAt(testCanvas, i, j), black) );
		}
	}
	free(testCanvas.pixels);
}

void test_canvas_pixelAt() {
	Canvas testCanvas = canvas_createCanvas(10, 20);
	Tuple black = tuple_createColor(0, 0, 0);
	for (int i = 0; i < testCanvas.width; i++) {
		for (int j = 0; j < testCanvas.height; j++) {
			TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(canvas_pixelAt(testCanvas, i, j), black));
		}
	}
	free(testCanvas.pixels);
}

void test_canvas_writePixel() {
	Canvas testCanvas = canvas_createCanvas(25, 20);
	Tuple red = tuple_createColor(1, 0, 0);
	canvas_writePixel(&testCanvas, red, 2, 3);
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(red, canvas_pixelAt(testCanvas, 2, 3)));
	free(testCanvas.pixels);
}

void test_canvas_canvasToPPM() {
	Canvas testCanvas = canvas_createCanvas(5, 3);
	Tuple c1 = tuple_createColor(1.5, 0, 0);
	Tuple c2 = tuple_createColor(0, 0.5, 0);
	Tuple c3 = tuple_createColor(-0.5, 0, 1);

	canvas_writePixel(&testCanvas, c1, 0, 0);
	canvas_writePixel(&testCanvas, c2, 2, 1);
	canvas_writePixel(&testCanvas, c3, 4, 2);


	int length;
	char** PPMdata = canvas_canvasToPPM(testCanvas, &length);
	printf("===================================\n");

	for (int i = 0; i < length; i++) {
		printf("%s", PPMdata[i]);

	}
	printf("===================================\n");

	TEST_ASSERT_EQUAL_STRING("255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 127 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n", PPMdata[3]);
}

void test_canvas_canvasToPPMNewline() {
	Canvas testCanvas = canvas_createCanvas(10, 2);
	Tuple c1 = tuple_createColor(1, 0.8, 0.6);

	for (int i = 0; i < testCanvas.height; i++) {
		for (int j = 0; j < testCanvas.width; j++) {
			canvas_writePixel(&testCanvas, c1, j, i);
		}
	}
	
	int length;
	char** PPMdata = canvas_canvasToPPM(testCanvas, &length);

	printf("===================================\n");

	for (int i = 0; i < length; i++) {
		printf("%s", PPMdata[i]);

	}
	printf("===================================\n");

	TEST_ASSERT_EQUAL_STRING("255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n", PPMdata[3]);
}

void test_canvas_canvasToPPMNewlineEnd() {
	Canvas testCanvas = canvas_createCanvas(5, 3);

	int length;
	char** PPMdata = canvas_canvasToPPM(testCanvas, &length);

	printf("===================================\n");

	for (int i = 0; i < length; i++) {
		printf("%s", PPMdata[i]);

	}
	printf("===================================\n");

	TEST_ASSERT_EQUAL_STRING("0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n", PPMdata[3]);
}

void test_canvas_RGBClamp() {
	float n1 = -0.1;
	float n2 = 65536;
	float n3 = 0;

	TEST_ASSERT_EQUAL_INT(0, canvas_RGBClamp(n1));
	TEST_ASSERT_EQUAL_INT(255, canvas_RGBClamp(n2));
	TEST_ASSERT_EQUAL_INT(0, canvas_RGBClamp(n3));

	TEST_ASSERT_EQUAL_INT(0, canvas_RGBClamp(n1*255));
	TEST_ASSERT_EQUAL_INT(255, canvas_RGBClamp(n2*255));
	TEST_ASSERT_EQUAL_INT(0, canvas_RGBClamp(n3*255));

}

int main() {
	RUN_TEST(test_canvas_createCanvas);
	RUN_TEST(test_canvas_pixelAt);
	RUN_TEST(test_canvas_writePixel);
	RUN_TEST(test_canvas_canvasToPPM);
	RUN_TEST(test_canvas_canvasToPPMNewline);
	RUN_TEST(test_canvas_RGBClamp);
	RUN_TEST(test_canvas_canvasToPPMNewlineEnd);
	return UNITY_END();
}