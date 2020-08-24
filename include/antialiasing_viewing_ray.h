#ifndef ANTIALIASING_VIEWING_RAY_H
#define ANTIALIASING_VIEWING_RAY_H

#include "Ray.h"
#include "Camera.h"

// Construct a viewing ray given a camera and subscripts to a pixel
//
// Inputs:
//   camera  Perspective camera object
//   i  pixel row index
//   j  pixel column index
//   width  number of pixels width of image
//   height  number of pixels height of image
// Outputs:
//   ray  viewing ray starting at camera shooting through pixel. When t=1, then
//     ray.origin + t*ray.direction should land exactly on the center of the
//     pixel (i,j)
void antialiasing_viewing_ray(
  const Camera & camera,
  const double i,
  const double j,
  const int width,
  const int height,
  Ray & ray);

#endif
