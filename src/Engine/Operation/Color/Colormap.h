#ifndef COLORMAP_H
#define COLORMAP_H

#include "../../common.h"


class Colormap
{
public:
  //Constructor / Destructor
  Colormap();
  ~Colormap();

public:
  void init();
  void choose(string name);

  inline vector<vec3>* get_colormap_selected(){return &colormap_selected;}

private:
  vector<string> colormap_name;
  vector<vector<vec3>> colormap_list;
  vector<vec3> colormap_selected;
};

#endif
