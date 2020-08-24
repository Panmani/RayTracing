#ifndef REFRACT_H
#define REFRACT_H
#include <Eigen/Core>

bool refract(const Eigen::Vector3d & d,
                        const Eigen::Vector3d & n,
                        const double n_nt,
                        Eigen::Vector3d & t);

#endif
