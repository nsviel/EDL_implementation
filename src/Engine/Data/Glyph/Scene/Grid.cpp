#include "Grid.h"


//Constructor / destructor
Grid::Grid(){
  //---------------------------

  this->name = "grid";
  this->grid_color = vec4(1, 1, 1, 1);
  this->nb_cell = 4;

  //---------------------------
}
Grid::~Grid(){
  //---------------------------

  delete glyph;

  //---------------------------
}

void Grid::create_glyph(){
  this->glyph = new Glyph();
  //---------------------------

  //Create glyph
  glyph->name = "grid";
  glyph->draw_line_width = 2;
  glyph->is_visible = true;
  glyph->draw_type_name = "line";
  glyph->is_permanent = true;
  glyph->unicolor = grid_color;

  //Construct glyph
  this->update_grid(nb_cell);

  //---------------------------
}
void Grid::update_grid(int value){
  vector<vec3>& XYZ = glyph->xyz;
  vector<vec4>& RGB = glyph->rgb;
  this->nb_cell = value;
  //---------------------------

  //Parameters
  XYZ.clear();
  RGB.clear();

  //Construct glyph
  for(int i=-nb_cell; i<=nb_cell; i++){
    XYZ.push_back(vec3((float)i, -(float)nb_cell, 0));
    XYZ.push_back(vec3((float)i, (float)nb_cell, 0));

    XYZ.push_back(vec3(-(float)nb_cell, (float)i, 0));
    XYZ.push_back(vec3((float)nb_cell, (float)i, 0));

    for(int j=0; j<4; j++){
      RGB.push_back(grid_color);
    }
  }

  //---------------------------
}
