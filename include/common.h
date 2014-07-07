#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <memory>


namespace Hodhr {

struct HodhrVertex
{
  float x, y, z;
  float nx, ny, nz;
  float s0, t0;
};

} // namespace Hodhr

int printOglError(std::string instruction);

#endif // COMMON_H
