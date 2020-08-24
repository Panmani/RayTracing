#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "read_json.h"
#include "write_ppm.h"
#include "viewing_ray.h"
#include "raycolor.h"
#include "antialiasing.h"
#include <Eigen/Core>
#include <vector>
#include <iostream>
#include <memory>
#include <limits>
#include <functional>
#include <string>

int main(int argc, char * argv[])
{
  Camera camera;
  std::vector< std::shared_ptr<Object> > objects;
  std::vector< std::shared_ptr<Light> > lights;
  // Read a camera and scene description from given .json file
  read_json(
    argc<=1?"../json/animated.json":argv[1],
    camera,
    objects,
    lights);

  // int width =  1920;
  // int height = 1080;
  int width =  640;
  int height = 360;
  std::vector<unsigned char> rgb_image(3*width*height);
  // // ==================== Infinite mirrors ====================
  // Camera moved_camera = camera;
  // for (size_t i = 0; i < 125; i++) {
  //   std::dynamic_pointer_cast<AreaLight>(lights[0])->c[2] -= 0.4;
  //   moved_camera.e[1] += 0.1;
  //   moved_camera.e[2] += 0.1;
  //   antialiasing(height, width, 4, moved_camera, objects, lights, rgb_image);
  //   write_ppm("./output_1/rgb_" + std::to_string(i) + ".ppm",rgb_image,width,height,3);
  // }
  // // ==================== Moving area light ====================
  // for (size_t i = 0; i < 50; i++) {
  //   std::dynamic_pointer_cast<AreaLight>(lights[0])->a[0] += 0.2;
  //   std::dynamic_pointer_cast<AreaLight>(lights[0])->b[2] += 0.2;
  //   if (i >= 0) {
  //     antialiasing(height, width, 4, camera, objects, lights, rgb_image);
  //     write_ppm("./output_2/rgb_" + std::to_string(i) + ".ppm",rgb_image,width,height,3);
  //   }
  // }
  // for (size_t i = 0; i < 100; i++) {
  //   std::dynamic_pointer_cast<AreaLight>(lights[0])->c[2] -= 0.5;
  //   if (i >= 0) {
  //     antialiasing(height, width, 4, camera, objects, lights, rgb_image);
  //     write_ppm("./output_3/rgb_" + std::to_string(i) + ".ppm",rgb_image,width,height,3);
  //   }
  // }
  // ==================== Counter rotation ====================
  Eigen::Affine3d rotation =
                Eigen::Affine3d(Eigen::AngleAxisd(1. / 180. * M_PI,
                                Eigen::Vector3d::UnitY()));
  Eigen::Affine3d rotation_p =
                Eigen::Affine3d(Eigen::AngleAxisd(-2. / 180. * M_PI,
                                Eigen::Vector3d::UnitY()));
  Eigen::Affine3d rotation_pp =
                Eigen::Affine3d(Eigen::AngleAxisd(3. / 180. * M_PI,
                                Eigen::Vector3d::UnitY()));
  double jump = -2. / 60;
  for (size_t i = 0; i < 360; i++) {
    if (i % 60 == 0) {
      jump = -jump;
    }
    for (size_t j = 0; j < 2; j++) {
      std::dynamic_pointer_cast<Sphere>(objects[j])->center =
            rotation * std::dynamic_pointer_cast<Sphere>(objects[j])->center;
      std::dynamic_pointer_cast<Sphere>(objects[j])->center[1] += jump;
    }
    for (size_t j = 2; j < 4; j++) {
      std::dynamic_pointer_cast<Sphere>(objects[j])->center =
            rotation_p * std::dynamic_pointer_cast<Sphere>(objects[j])->center;
      std::dynamic_pointer_cast<Sphere>(objects[j])->center[1] -= jump;
    }
    std::dynamic_pointer_cast<AreaLight>(lights[0])->c =
            rotation_pp * std::dynamic_pointer_cast<AreaLight>(lights[0])->c;
    if (0 <= i && i <= 360) {
      antialiasing(height, width, 4, camera, objects, lights, rgb_image);
      write_ppm("rgb_" + std::to_string(i) + ".ppm",rgb_image,width,height,3);
    }
  }
}
