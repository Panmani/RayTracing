#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include "refract.h"
#include "dielectrics_color.h"

bool raycolor(
  const Ray & ray,
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  bool is_hit = false;
  int idx_hit = 0;
  double t_hit = std::numeric_limits<double>::infinity();
  Eigen::Vector3d n_hit = Eigen::Vector3d(0,0,0);

  is_hit = first_hit(ray, min_t, objects, idx_hit, t_hit, n_hit);

  int max_recursive_calls = 20;

  if (is_hit and num_recursive_calls < max_recursive_calls) {
    rgb += (objects[idx_hit]->material->ka.array() * Eigen::Vector3d(1,1,1).array()).matrix();;
    rgb += blinn_phong_shading(ray, idx_hit, t_hit, n_hit, objects, lights);
    rgb += dielectrics_color(ray, objects, lights, num_recursive_calls + 1,
                             is_hit, idx_hit, t_hit, n_hit);
  } else {
    rgb += Eigen::Vector3d(0,0,0);
  }

  return is_hit;

  ////////////////////////////////////////////////////////////////////////////
}
