#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code from computer-graphics-raster-images or email
  // jacobson@cs.toronto.edu for correct code.

  std::ofstream file;
  file.open(filename, std::ofstream::out);

  if (!file) {
    std::cerr << "Failed to open " << filename << std::endl;
    return false;
  }

  file << "P6" << std::endl;
  file << width << std::endl;
  file << height << std::endl;
  file << 255 << std::endl;

  if (num_channels == 3) {
    for (const auto &p : data) {
      file << p;
    }    
  } else {
    for (const auto &p : data) {
      file << p;
      file << p;
      file << p;
    }    
  }

  if (file.fail()) {
    std::cerr << "Failed to write into " << filename << std::endl;
    file.clear();
    return false;
  }

  file.close();

  return true;

  ////////////////////////////////////////////////////////////////////////////
}
