#ifndef OBJECT_GRID_H
#define OBJECT_GRID_H

#include "../Base/Glyph_source.h"


class Grid : public Glyph_source
{
public:
  //Constructor / Destructor
  Grid();
  ~Grid();

public:
  void create_glyph();
  void update_grid(int value);

private:
  vec4 grid_color;
  int nb_cell;
};

#endif
