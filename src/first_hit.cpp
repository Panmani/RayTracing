#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  double t_hit = std::numeric_limits<double>::infinity();
  double cur_t;
  Eigen::Vector3d cur_n;
  bool is_hit = false;
  for (int i = 0; i < objects.size(); i++) {
    if (objects[i]->intersect(ray, min_t, cur_t, cur_n) and cur_t < t_hit) {
      t_hit = cur_t;
      hit_id = i;
      n = cur_n;
      is_hit = true;
    }
  }

  if (is_hit) t = t_hit;

  return is_hit;

  ////////////////////////////////////////////////////////////////////////////
}

