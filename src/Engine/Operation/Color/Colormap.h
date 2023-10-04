#ifndef COLORMAP_H
#define COLORMAP_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace glm;


class Colormap
{
public:
  //Constructor / Destructor
  Colormap();
  ~Colormap();

public:
  void init();
  void choose(string name);
  vec4 random_color();

  inline vector<vec3>* get_colormap_selected(){return &colormap_selected;}

private:
  vector<string> colormap_name;
  vector<vector<vec3>> colormap_list;
  vector<vec3> colormap_selected;
};

#endif
