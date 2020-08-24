#include <Eigen/Core>

bool refract(const Eigen::Vector3d & d,
                        const Eigen::Vector3d & n,
                        const double n_nt,
                        Eigen::Vector3d & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // n_nt = n / n_t

  double dn = d.normalized().dot(n);
  Eigen::Vector3d left = n_nt * (d.normalized() - n * dn);
  double in_sqrt = 1 - pow(n_nt, 2) * (1 - pow(dn, 2));
  if (in_sqrt < 0) {
    return false;
  }

  Eigen::Vector3d right = n * pow(in_sqrt, 0.5);
  t = (left - right).normalized();
  return true;

  ////////////////////////////////////////////////////////////////////////////
}
