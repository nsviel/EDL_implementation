#ifndef OBJECT_GRID_PLANE_H
#define OBJECT_GRID_PLANE_H

#include "../Base/Glyph_source.h"


class Grid_plane : public Glyph_source
{
public:
  //Constructor / Destructor
  Grid_plane();
  ~Grid_plane();

public:
  void create_grid();
  void create_grid_sub();
  void create_grid_plane();

  void update_grid(int value);
  void update_grid_sub(int value);
  void update_grid_plane(int value);

  inline Glyph* get_grid(){return grid;}
  inline Glyph* get_grid_sub(){return grid_sub;}
  inline Glyph* get_grid_plane(){return grid_plane;}
  inline vec4* get_grid_color(){return &grid_color;}

private:
  Glyph* grid;
  Glyph* grid_sub;
  Glyph* grid_plane;
  vec4 grid_color;
  vec4 grid_sub_color;
  int nb_cell;
};

#endif
