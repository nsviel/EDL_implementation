#ifndef HEATMAP_H
#define HEATMAP_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace glm;

class Colormap;


class Heatmap
{
public:
  //Constructor / Destructor
  Heatmap();
  ~Heatmap();

public:

private:
  Colormap* colormapManager;

  vec2 range_norm;
  vec2 range_height;
  vec2 range_intensity;
  bool is_normalization;
  int heatmap_mode;
};

#endif
