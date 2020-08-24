#include "dielectrics_color.h"
#include "raycolor.h"
#include "reflect.h"
#include "refract.h"
#include <iostream>

Eigen::Vector3d dielectrics_color(
  const Ray & ray,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  const bool is_hit,
  const int idx_hit,
  const double t_hit,
  const Eigen::Vector3d & n_hit)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  double c = 0.0;
  Eigen::Vector3d k_rgb = Eigen::Vector3d(0,0,0);
  Eigen::Vector3d color_r = Eigen::Vector3d(0,0,0);
  Eigen::Vector3d color_t = Eigen::Vector3d(0,0,0);
  if (objects[idx_hit]->material->is_dielectric) {
    // std::cout << objects[idx_hit]->material->is_dielectric << std::endl;
    Ray reflected_ray;
    reflected_ray.origin = ray.origin + t_hit * ray.direction;
    reflected_ray.direction = reflect(ray.direction.normalized(), n_hit);
    Ray refracted_ray;
    refracted_ray.origin = ray.origin + t_hit * ray.direction;
    Eigen::Vector3d t;
    if (ray.direction.dot(n_hit) < 0.0) {
      // Enter object
      refract(ray.direction.normalized(),
              n_hit,
              1.0 / objects[idx_hit]->material->n_t,
              t);
      c = -ray.direction.normalized().dot(n_hit);
      k_rgb = Eigen::Vector3d(1.0, 1.0, 1.0);
    } else {
      k_rgb = Eigen::Vector3d(
                  exp(-objects[idx_hit]->material->a_rgb[0] * t_hit),
                  exp(-objects[idx_hit]->material->a_rgb[1] * t_hit),
                  exp(-objects[idx_hit]->material->a_rgb[2] * t_hit));
      if (refract(ray.direction.normalized(),
        // Exit object
                  -n_hit,
                  objects[idx_hit]->material->n_t,
                  t)) {
        c = t.dot(n_hit);
      } else {
        // Total internal reflection
        raycolor(reflected_ray, 1e-7, objects, lights, num_recursive_calls + 1, color_r);
        return (k_rgb.array() * color_r.array()).matrix();
      }
    }
    // Exit object
    double R0 = pow(objects[idx_hit]->material->n_t - 1.0, 2) /
                pow(objects[idx_hit]->material->n_t + 1.0, 2);
    double R = R0 + (1.0 - R0) * pow(1.0 - c, 5);
    refracted_ray.direction = t;
    raycolor(reflected_ray, 1e-7, objects, lights, num_recursive_calls + 1, color_r);
    raycolor(refracted_ray, 1e-7, objects, lights, num_recursive_calls + 1, color_t);
    return (k_rgb.array() * (R * color_r + (1 - R) * color_t).array()).matrix();
  } else {
    Ray reflected_ray;
    reflected_ray.origin = ray.origin + t_hit * ray.direction;
    reflected_ray.direction = reflect(ray.direction.normalized(), n_hit);
    Eigen::Vector3d color_r = Eigen::Vector3d(0,0,0);
    raycolor(reflected_ray, 1e-7, objects, lights, num_recursive_calls + 1, color_r);
    return (objects[idx_hit]->material->km.array() * color_r.array()).matrix();
  }

  return Eigen::Vector3d(0,0,0);
  ////////////////////////////////////////////////////////////////////////////
}
