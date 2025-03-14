#include "Camera.h"
Camera camera_createCamera(int hszie, int vsize, float fov, Mat4 transform){
    Camera newCamera;
    newCamera.hsize = hszie;
    newCamera.vsize = vsize;
    newCamera.fov = fov;
    
    if (transform == NULL) {
        Mat4 iden = MAT4_IDENTITY;
        mat_mat4Copy(iden, newCamera.transform);
    } 
    else {
        mat_mat4Copy(transform, newCamera.transform);
    }

    float halfView = tanf(newCamera.fov / 2.0f);
    float aspect = (float)newCamera.hsize / (float)newCamera.vsize;
    if (aspect >= 1.0f) {
        newCamera.halfWidth = halfView;
        newCamera.halfHeight = halfView / aspect;
    }
    else {
        newCamera.halfWidth = halfView * aspect;
        newCamera.halfHeight = halfView;
    }

    newCamera.pixelSize = (newCamera.halfWidth * 2) / (float)newCamera.hsize;

    return newCamera;
}

Ray camera_rayForPixel(Camera camera, int pixelx, int pixely){
   float xoffset = (pixelx + 0.5f) * camera.pixelSize;
   float yoffset = (pixely + 0.5f) * camera.pixelSize;

   float worldx = camera.halfWidth - xoffset;
   float worldy = camera.halfHeight - yoffset;

   Mat4 invCameraTransform;
   mat_mat4Inverse(camera.transform, invCameraTransform);
   Tuple pixel = mat_mat4MultuplyTuple(invCameraTransform, tuple_createPoint(worldx, worldy, -1));
   Tuple origin = mat_mat4MultuplyTuple(invCameraTransform, tuple_createPoint(0, 0, 0));
   Tuple direction = tuple_vectorNormalize(tuple_tupleSub(pixel, origin));
   return ray_createRay(origin, direction);
}

Canvas camera_render(Camera cam, World world){
    Canvas image = canvas_createCanvas(cam.hsize, cam.vsize);

    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            Ray ray = camera_rayForPixel(cam, x, y);
            Tuple color = world_worldColorAt(world, ray);
            canvas_writePixel(&image, color, x, y);
        }
    }

    return image;
}
