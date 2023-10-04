#ifndef COLOR_FUNCTION_H
#define COLOR_FUNCTION_H

#include "../common.h"


//Get a RGB random color
glm::vec4 random_color();


class Color
{
public:
  //Constructor / Destructor
  Color();
  ~Color();

public:
  void update_configuration();

  //Colorization functions
  void make_colorization(Set* set, int ID_object);
  void make_colorization(Cloud* cloud, vec4 RGB_in);
  void make_colorization_specific(Cloud* cloud);

  //Specific functions
  void color_unicolor(Object* object, vec4 color);
  void color_intensity(Cloud* cloud);
  void color_heatmap(Cloud* cloud);

  //Color cloud functions
  void set_color_new(Set* set, vec4 RGBA);
  void set_color_enhanced(Set* set);
  void set_color_random(Set* set);
  void set_color_initial(Set* set);
  void set_color_RGB(Set* set);
  void set_color_I(Set* set);
  string get_color_mode_name();

  inline int* get_color_mode(){return &color_mode;}
  inline vec2* get_range_intensity(){return &range_intensity;}

private:
  vec2 range_intensity;
  vec4 specific_color;
  int color_mode;
};

#endif
