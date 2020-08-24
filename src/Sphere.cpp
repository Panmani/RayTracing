#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  Eigen::Vector3d e_c = ray.origin - center;
  double dd = ray.direction.dot(ray.direction);

  double de_c = ray.direction.dot(e_c);
  double de_c_2 = pow(de_c, 2.0);
  double dde_ce_c_R_2 = dd * (e_c.dot(e_c) - pow(radius, 2.0));
  double discriminant = de_c_2 - dde_ce_c_R_2;

  if (discriminant >= 0) {
    // Hits the object
    double numerator_plus = -de_c + sqrt(discriminant);
    double numerator_minus = -de_c - sqrt(discriminant);
    double t_plus = numerator_plus / dd;
    double t_minus = numerator_minus / dd;

    if (fmin(t_plus, t_minus) > min_t) {
      // In front of the image plane
      t = fmin(t_plus, t_minus);
      Eigen::Vector3d p = ray.origin + t * ray.direction;
      n = (p - center) / radius;
      return true;
    }
    
  }

  return false;

  ////////////////////////////////////////////////////////////////////////////
}

