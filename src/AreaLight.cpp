#include "AreaLight.h"
#include <stdlib.h>

void AreaLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  Eigen::Vector3d p = c +
                      ((double) rand() / (RAND_MAX)) * a +
                      ((double) rand() / (RAND_MAX)) * b;

  d = (p - q).normalized();
  max_t = (p - q).dot(d);

  ////////////////////////////////////////////////////////////////////////////
}
