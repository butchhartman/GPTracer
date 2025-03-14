#pragma once
#include "Canvas.h"
#include "World.h"

typedef struct {
    int hsize;
    int vsize;
    float fov;
    Mat4 transform;
    float halfWidth;
    float halfHeight;
    float pixelSize;
} Camera;

Camera camera_createCamera(int hszie, int vsize, float fov, Mat4 transform);
Ray camera_rayForPixel(Camera camera, int pixelx, int pixely);
Canvas camera_render(Camera cam, World world);