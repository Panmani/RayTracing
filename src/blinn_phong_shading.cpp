#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include "Light.h"
#include "AreaLight.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id,
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  Eigen::Vector3d color = Eigen::Vector3d(0,0,0);
  Eigen::Vector3d cur_d;
  double cur_max_t;

  Ray l;
  int shadow_hit_id;
  double shadow_hit_t;
  Eigen::Vector3d shadow_hit_n;
  bool shadow_is_hit;
  for (int i = 0; i < lights.size(); i++) {
    if (std::dynamic_pointer_cast<AreaLight>(lights[i])) {
      // Area light, soft shadows
      int test_num = 32;
      for (size_t N = 0; N < test_num; N++) {
        lights[i]->direction(ray.origin + t * ray.direction, cur_d, cur_max_t);
        l.origin = ray.origin + t * ray.direction;
        l.direction = (cur_max_t * cur_d).normalized();

        shadow_is_hit = first_hit(l, 1e-7, objects, shadow_hit_id, shadow_hit_t, shadow_hit_n);

        if (!(shadow_is_hit and shadow_hit_t <= cur_max_t)) {
          Eigen::Vector3d kd_I = (objects[hit_id]->material->kd.array() * lights[i]->I.array()).matrix();
          double max_nl = fmax(n.dot(cur_d), 0);
          Eigen::Vector3d ks_I = (objects[hit_id]->material->ks.array() * lights[i]->I.array()).matrix();
          Eigen::Vector3d h = (cur_d + (-ray.direction.normalized())).normalized();
          double max_hn_p = pow(fmax(h.dot(n), 0), objects[hit_id]->material->phong_exponent);
          color += (1.0 / test_num) * (kd_I * max_nl + ks_I * max_hn_p);
        }
      }
    } else {
      // Point or directional light
      lights[i]->direction(ray.origin + t * ray.direction, cur_d, cur_max_t);
      l.origin = ray.origin + t * ray.direction;
      if (std::isinf(cur_max_t))
        l.direction = cur_d;
      else
        l.direction = (cur_max_t * cur_d).normalized();

      shadow_is_hit = first_hit(l, 1e-7, objects, shadow_hit_id, shadow_hit_t, shadow_hit_n);

      if (!(shadow_is_hit and shadow_hit_t <= cur_max_t)) {
        Eigen::Vector3d kd_I = (objects[hit_id]->material->kd.array() * lights[i]->I.array()).matrix();
        double max_nl = fmax(n.dot(cur_d), 0);
        Eigen::Vector3d ks_I = (objects[hit_id]->material->ks.array() * lights[i]->I.array()).matrix();
        Eigen::Vector3d h = (cur_d + (-ray.direction.normalized())).normalized();
        double max_hn_p = pow(fmax(h.dot(n), 0), objects[hit_id]->material->phong_exponent);
        color += kd_I * max_nl + ks_I * max_hn_p;
      }
    }


  }

  return color;

  ////////////////////////////////////////////////////////////////////////////
}
