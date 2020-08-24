#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  double nd = normal.dot(ray.direction);
  if (nd != 0) {
  	double numerator = normal.dot(point) - normal.dot(ray.origin);
  	double t_test = numerator / nd;
  	if (t_test > min_t) {
  	  t = t_test;
  	  n = normal;
  	  return true;
  	}
  }

  return false;

  ////////////////////////////////////////////////////////////////////////////
}

