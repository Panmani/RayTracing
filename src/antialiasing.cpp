#include "antialiasing.h"

#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "read_json.h"
#include "write_ppm.h"
#include "antialiasing_viewing_ray.h"
#include "raycolor.h"
#include <stdlib.h>
#include <iostream>

void antialiasing(
  const int height,
  const int width,
  const int n,
  const Camera & camera,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  std::vector<unsigned char> & rgb_image)
{
  for(unsigned i=0; i<height; ++i)
  {
    for(unsigned j=0; j<width; ++j)
    {

      Eigen::Vector3d c_ij(0,0,0);
      for (size_t p = 0; p < n; p++) {
        for (size_t q = 0; q < n; q++) {
          // Set background color
          Eigen::Vector3d rgb(0,0,0);
          // Compute viewing ray
          Ray ray;
          antialiasing_viewing_ray(camera,
                      i + (p + ((double) rand() / (RAND_MAX))) / n,
                      j + (q + ((double) rand() / (RAND_MAX))) / n,
                      width, height, ray);

          // Shoot ray and collect color
          raycolor(ray,1.0,objects,lights,0,rgb);
          c_ij += rgb;
        }
      }
      c_ij /= pow(n, 2);
      // Write double precision color into image
      auto clamp = [](double s){ return std::max(std::min(s,1.0),0.0);};
      rgb_image[0+3*(j+width*i)] = 255.0*clamp(c_ij(0));
      rgb_image[1+3*(j+width*i)] = 255.0*clamp(c_ij(1));
      rgb_image[2+3*(j+width*i)] = 255.0*clamp(c_ij(2));
    }
    std::cout << "Progress: "
              << i + 1 << " / " << height
              << std::endl;
  }

}
