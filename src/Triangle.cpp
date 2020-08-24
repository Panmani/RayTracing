#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  Eigen::Vector3d ab = std::get<1>(corners) - std::get<0>(corners);
  Eigen::Vector3d ac = std::get<2>(corners) - std::get<0>(corners);
  Eigen::Vector3d normal = ab.cross(ac).normalized();

  Eigen::Vector3d h;
  double nd = normal.dot(ray.direction);
  if (nd != 0) {
    double numerator = normal.dot(std::get<0>(corners)) - normal.dot(ray.origin);
    double t_test = numerator / nd;
    if (t_test > min_t) {
      double area_tri = abs((ab).cross(ac).norm() / 2);

      h = ray.origin + t_test * ray.direction;
      Eigen::Vector3d ha = std::get<0>(corners) - h;
      Eigen::Vector3d hb = std::get<1>(corners) - h;
      Eigen::Vector3d hc = std::get<2>(corners) - h;
      double area_a = abs(hb.cross(hc).norm() / 2);
      double area_b = abs(ha.cross(hc).norm() / 2);
      double area_c = abs(ha.cross(hb).norm() / 2);
      double area_test = area_a + area_b + area_c;

      if (abs(area_test - area_tri) < 1e-7) {
        t = t_test;
        n = normal;
        return true;
      }
    }
  }

  return false;

  ////////////////////////////////////////////////////////////////////////////
}


