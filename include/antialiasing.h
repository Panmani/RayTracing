#ifndef ANTIALIASING_H
#define ANTIALIASING_H

#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "read_json.h"
#include "write_ppm.h"
#include "viewing_ray.h"
#include "raycolor.h"

void antialiasing(
  const int height,
  const int width,
  const int n,
  const Camera & camera,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  std::vector<unsigned char> & rgb_image);

#endif
