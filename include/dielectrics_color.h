#ifndef DIELECTRICS_COLOR_H
#define DIELECTRICS_COLOR_H
#include "Ray.h"
#include "Object.h"
#include "Light.h"
#include <Eigen/Core>
#include <vector>

Eigen::Vector3d dielectrics_color(
  const Ray & ray,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  const bool is_hit,
  const int idx_hit,
  const double t_hit,
  const Eigen::Vector3d & n_hit);

#endif
